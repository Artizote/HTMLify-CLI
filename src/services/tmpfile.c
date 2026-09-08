// TmpFile

#include <string.h>
#include "services/tmpfile.h"
#include "services/blob.h"
#include "utils.h"
#include "curl/curl.h"
#include "cJSON.h"


// Helper functions
static size_t curl_upload_read_callback(char*, size_t, size_t, void*);
static int curl_upload_seek_callback(void*, curl_off_t, int);
static int curl_upload_progress_callback(void *, curl_off_t , curl_off_t , curl_off_t , curl_off_t );


struct tmpfile_upload_state {
    FILE *file;
    curl_off_t size;
    curl_off_t position;
};


TmpFile *TmpFile_new(void) {
    TmpFile *tmpfile = malloc(sizeof(TmpFile));
    tmpfile->id = malloc(9);
    tmpfile->id[0] = '\0'; 
    tmpfile->name = malloc(1025);
    tmpfile->name[0] = '\0'; 
    tmpfile->blob = Blob_new();
    return tmpfile;
}

void TmpFile_init(TmpFile *tmpfile, const char *id, const char *name, const char *blob_hash) {
    strncpy(tmpfile->id, id, 8);
    tmpfile->id[8] = '\0';
    strncpy(tmpfile->name, name, 1024);
    tmpfile->name[8] = '\0';
    strncpy(tmpfile->blob->hash, blob_hash, 64);
    if (tmpfile->blob != NULL) {
        Blob_free(tmpfile->blob);
    }
    tmpfile->blob = Blob_get(blob_hash);
}

void TmpFile_init_from_json(TmpFile *tmpfile, const cJSON *json) {
    cJSON *id_object = cJSON_GetObjectItem(json, "id");
    cJSON *name_object = cJSON_GetObjectItem(json, "name");
    cJSON *blob_hash_object = cJSON_GetObjectItem(json, "blob_hash");
    TmpFile_init(tmpfile, id_object->valuestring, name_object->valuestring, blob_hash_object->valuestring);
}

TmpFile *TmpFile_get(const char *id) {
    TmpFile *tmpfile = NULL;
    char *api_url;
    CURL *handle;
    cJSON *res_json = NULL;
    CURLcode res_code;
    long http_res_code;
    
    api_url = make_api_url("/tmp-files/");
    append_string_to_url(api_url, id);

    handle = curl_easy_init();
    if (!handle) goto end;
    curl_easy_setopt(handle, CURLOPT_URL, api_url);

    res_json = curl_easy_perform_return_json(handle, &res_code);
    curl_easy_getinfo(handle, CURLINFO_HTTP_CODE, &http_res_code);
    if ((http_res_code < 200) || (299 < http_res_code)) goto end;

    tmpfile = TmpFile_new();
    TmpFile_init_from_json(tmpfile, res_json);

end:
    cJSON_Delete(res_json);
    curl_easy_cleanup(handle);
    free(api_url);
    return tmpfile;
}

// Upload the contents from `file` and create a new `TmpFile`
TmpFile *TmpFile_create(FILE *file, const char *name, Progress *progress) {
    TmpFile *tmpfile = NULL;
    char *api_url;
    CURL *handle;
    cJSON *res_json = NULL;
    CURLcode res_code;
    curl_mime *form = NULL;
    curl_mimepart *field = NULL;
    long http_res_code, file_size;
    const char *filename = name ? name : "tmpfile";

    if (!file) {
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    api_url = make_api_url("/tmp-files");

    handle = curl_easy_init();
    if (!handle) goto end;
    curl_easy_setopt(handle, CURLOPT_URL, api_url);
    curl_easy_setopt(handle, CURLOPT_POST, 1L);

    form = curl_mime_init(handle);

    // file field
    field = curl_mime_addpart(form);
    struct tmpfile_upload_state tus = {file, file_size, 0};
    curl_mime_name(field, "file");
    curl_mime_data_cb(field, file_size, curl_upload_read_callback, curl_upload_seek_callback, NULL, &tus);
    curl_mime_filename(field, filename);

    // name (of file) field
    field = curl_mime_addpart(form);
    curl_mime_name(field, "name");
    curl_mime_data(field, filename, CURL_ZERO_TERMINATED);

    curl_easy_setopt(handle, CURLOPT_MIMEPOST, form);

    if (progress) {
        curl_easy_setopt(handle, CURLOPT_XFERINFOFUNCTION, curl_upload_progress_callback);
        curl_easy_setopt(handle, CURLOPT_XFERINFODATA, progress);
        curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 0L);
    }

    res_json = curl_easy_perform_return_json(handle, &res_code);
    curl_easy_getinfo(handle, CURLINFO_HTTP_CODE, &http_res_code);
    if ((http_res_code < 200) || (299 < http_res_code)) goto end;

    tmpfile = TmpFile_new();
    TmpFile_init_from_json(tmpfile, res_json);

end:
    cJSON_Delete(res_json);
    free(handle);
    free(api_url);
    return tmpfile;
}

TmpFile *TmpFile_upload(const char *filepath, const char *name, Progress *progress) {
    FILE *file = fopen(filepath, "rb");
    if (!file) return NULL;
    char *filename = name ? strdup(name) : filename_from_filepath(filepath);
    if (progress && !progress->target) {
        long size;
        fseek(file, 0L, SEEK_END);
        size = ftell(file);
        fseek(file, 0L, SEEK_SET);
        progress->target = size;
    }
    TmpFile *tmpfile = TmpFile_create(file, filename, progress);
    fclose(file);
    free(filename);
    return tmpfile;
}

bool TmpFile_write(TmpFile *tmpfile, FILE *file, Progress *progress) {
    if (!tmpfile->blob) return false;
    return Blob_write(tmpfile->blob, file, progress);
}

bool TmpFile_download(TmpFile *tmpfile, char *filepath, Progress *progress) {
    if (!tmpfile->blob) return false;
    return Blob_download(tmpfile->blob, filepath, progress);
}

void TmpFile_free(TmpFile *tmpfile) {
    Blob_free(tmpfile->blob);
    free(tmpfile->id);
    free(tmpfile->name);
    free(tmpfile);
}


static size_t curl_upload_read_callback(char *buffer, size_t size, size_t nitems, void *arg) {
    struct tmpfile_upload_state *p = (struct tmpfile_upload_state *)arg;
    size_t sz = (size_t)(p->size - p->position), read = 0;

    nitems *= size;
    if(sz > nitems)
        sz = nitems;

    if(sz) {
        fseek(p->file, p->position, SEEK_SET);
        read = fread(buffer, 1, sz, p->file);
    }

    p->position += read;
    return read;
}

static int curl_upload_seek_callback(void *arg, curl_off_t offset, int origin) {
    struct tmpfile_upload_state *p = (struct tmpfile_upload_state *)arg;

    switch (origin) {
        case SEEK_END:
            offset += p->size;
            break;
        case SEEK_CUR:
            offset += p->position;
            break;
        case SEEK_SET:
            break;
        default:
            return CURL_SEEKFUNC_CANTSEEK;
    }

    if (offset < 0 || offset > p->size)
        return CURL_SEEKFUNC_FAIL;

    p->position = offset;

    return CURL_SEEKFUNC_OK;
}

static int curl_upload_progress_callback(void *progress, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    UNUSED(dltotal + ultotal + dlnow);
    size_t update = ulnow - ((Progress*)progress)->current;
    Progress_update(progress, update);
    printf("%s\r", Progress_to_string(progress, NULL));
    return 0;
}

