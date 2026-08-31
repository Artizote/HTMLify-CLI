// BLob

#include <string.h>
#include "services/blob.h"
#include "utils.h"
#include "models/progress.h"
#include "curl/curl.h"
#include "cJSON.h"


// Helper functions
static int curl_download_progress_callback(void *, curl_off_t , curl_off_t , curl_off_t , curl_off_t );


Blob *Blob_new(void) {
    Blob *blob = malloc(sizeof(Blob));
    blob->hash[0] = '\0';
    blob->size = 0;
    return blob;
}

void Blob_init(Blob *blob, const char *hash, size_t size) {
    strncpy(blob->hash, hash, 64);
    blob->hash[64] = '\0';
    blob->size = size;
}

void Blob_init_from_json(Blob *blob, cJSON *json) {
    cJSON *hash = cJSON_GetObjectItem(json, "hash");
    cJSON *size = cJSON_GetObjectItem(json, "size");
    Blob_init(blob, hash->valuestring, size->valuedouble);
}

Blob *Blob_get(const char *hash) {
    char *api_url = NULL;
    cJSON *res_json = NULL;
    CURLcode res_code;
    CURL *handle;
    Blob *blob = NULL;
    long http_res_code;

    api_url = make_api_url("/blob/");
    append_string_to_url(api_url, hash);

    handle = curl_easy_init();
    if (!handle) goto end;
    curl_easy_setopt(handle, CURLOPT_URL, api_url);
    res_json = curl_easy_perform_return_json(handle, &res_code);
    if (res_code != CURLE_OK) goto end;
    curl_easy_getinfo(handle, CURLINFO_HTTP_CODE, &http_res_code);
    if (200 > http_res_code || http_res_code > 299) goto end;

    blob = Blob_new();
    Blob_init_from_json(blob, res_json);

end:
    cJSON_Delete(res_json);
    curl_easy_cleanup(handle);
    free(api_url);

    return blob;
}

bool Blob_write(Blob *blob, FILE *file, Progress *progress) {
    char *api_url = NULL;
    CURLcode res_code;
    CURL *handle;
    bool success = false;

    api_url = make_api_url("/blob/");
    append_string_to_url(api_url, blob->hash);
    append_string_to_url(api_url, "/content");

    handle = curl_easy_init();
    if (!handle) goto end;

    curl_easy_setopt(handle, CURLOPT_URL, api_url);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(handle, CURLOPT_FAILONERROR, 1L);

    if (progress) {
        curl_easy_setopt(handle, CURLOPT_XFERINFOFUNCTION, curl_download_progress_callback);
        curl_easy_setopt(handle, CURLOPT_XFERINFODATA, progress);
        curl_easy_setopt(handle, CURLOPT_NOPROGRESS, 0L);
    }

    res_code = curl_easy_perform(handle);
    if (res_code != CURLE_OK) goto end;

    success = true;

end:
    curl_easy_cleanup(handle);
    free(api_url);
    return success;
}

bool Blob_download(Blob *blob, const char *filepath, Progress *progress) {
    FILE *file = fopen(filepath, "w");
    return Blob_write(blob, file, progress);
}

void Blob_free(Blob *blob) {
    free(blob);
}


static int curl_download_progress_callback(void *progress, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
    UNUSED(dltotal + ultotal + ulnow);
    size_t update = dlnow - ((Progress*)progress)->current;
    Progress_update(progress, update);
    return 0;
}
