// ShortLink

#include <malloc.h>
#include <string.h>
#include "curl/curl.h"
#include "services/shortlink.h"
#include "utils.h"
#include "curl/curl.h"
#include "cJSON.h"


ShortLink *ShortLink_new(void) {
    ShortLink *shortlink = malloc(sizeof(ShortLink));
    return shortlink;
}

void ShortLink_init(ShortLink *shortlink, int id, char *href, char *_short, int hits, char *url) {
    if (!shortlink) return;
    shortlink->id     = id;
    shortlink->href   = strdup(href);
    shortlink->_short = strdup(_short);
    shortlink->hits   = hits;
    shortlink->url    = strdup(url);
}

void ShortLink_init_from_json(ShortLink *shortlink, const cJSON *json) {
    if (!shortlink) return;
    shortlink->id     = cJSON_GetObjectItem(json, "id")->valuedouble;
    shortlink->href   = strdup(cJSON_GetObjectItem(json, "href")->valuestring);
    shortlink->_short = strdup(cJSON_GetObjectItem(json, "short")->valuestring);
    shortlink->hits   = cJSON_GetObjectItem(json, "hits")->valueint;
    shortlink->url    = strdup(cJSON_GetObjectItem(json, "url")->valuestring);
}

ShortLink *ShortLink_create(char *url, bool new) {
    ShortLink *shortlink = NULL;
    cJSON
    *json_body = NULL,
    *json_item_href = NULL,
    *json_item_new = NULL,
    *res_json = NULL
    ;
    CURL *handle = NULL;
    struct curl_slist *headers = NULL;
    char
    *api_url = NULL,
    *json_body_string = NULL
    ;

    api_url = make_api_url("/shortlinks");

    json_body = cJSON_CreateObject();
    json_item_href = cJSON_CreateString(url);
    json_item_new = new ? cJSON_CreateTrue() : cJSON_CreateFalse() ;
    if (!json_body || !json_item_href || !json_item_new) goto end;
    cJSON_AddItemToObject(json_body, "href", json_item_href);
    cJSON_AddItemToObject(json_body, "new", json_item_new);

    handle = curl_easy_init();
    if (!handle) goto end;
    curl_easy_setopt(handle, CURLOPT_URL, api_url);
    json_body_string = cJSON_Print(json_body);
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, json_body_string);
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);

    CURLcode res_code;
    res_json = curl_easy_perform_return_json(handle, &res_code);
    if (!res_json) goto end;
    if (res_code != CURLE_OK) goto end;

    long http_res_code;
    curl_easy_getinfo(handle, CURLINFO_HTTP_CODE, &http_res_code);
    if (200 > http_res_code || http_res_code > 299) goto end;

    shortlink = ShortLink_create_from_json(res_json);

end:
    cJSON_Delete(res_json);
    curl_slist_free_all(headers);
    curl_easy_cleanup(handle);
    cJSON_Delete(json_body);
    free(json_body_string);
    free(api_url);

    return shortlink;
}

ShortLink *ShortLink_create_from_json(const cJSON *json) {
    if (!json) return NULL;
    ShortLink *shortlink = ShortLink_new();
    ShortLink_init_from_json(shortlink, json);
    return shortlink;
}

ShortLink *ShortLink_get_by_id(int id) {
    ShortLink *shortlink = NULL;
    CURL *handle = NULL;
    cJSON *res_json = NULL;
    char *api_url;

    api_url = make_api_url("/shortlinks");
    append_string_to_url(api_url, "?id=");
    char id_str[10];
    sprintf(id_str, "%d", id);
    append_string_to_url(api_url, id_str);
    
    handle = curl_easy_init();
    if (!handle) goto end;
    curl_easy_setopt(handle, CURLOPT_URL, api_url);

    CURLcode res_code;
    res_json = curl_easy_perform_return_json(handle, &res_code);

    if (res_code != CURLE_OK) goto end;

    long http_res_code;
    curl_easy_getinfo(handle, CURLINFO_HTTP_CODE, &http_res_code);
    if (200 > http_res_code || http_res_code > 299) goto end;

    shortlink = ShortLink_create_from_json(res_json);

end:
    cJSON_Delete(res_json);
    curl_easy_cleanup(handle);
    free(api_url);

    return shortlink;
}

ShortLink *ShortLink_get_by_short(const char *_short) {
    ShortLink *shortlink = NULL;
    CURL *handle = NULL;
    cJSON *res_json = NULL;
    char *api_url = NULL;

    if (!_short) goto end;

    api_url = make_api_url("/shortlinks");
    append_string_to_url(api_url, "?short=");
    append_string_to_url(api_url, _short);

    handle = curl_easy_init();
    if (!handle) goto end;
    curl_easy_setopt(handle, CURLOPT_URL, api_url);

    CURLcode res_code;
    res_json = curl_easy_perform_return_json(handle, &res_code);

    if (res_code != CURLE_OK) goto end;

    long http_res_code;
    curl_easy_getinfo(handle, CURLINFO_HTTP_CODE, &http_res_code);
    if (200 > http_res_code || http_res_code > 299) goto end;

    shortlink = ShortLink_create_from_json(res_json);

end:
    cJSON_Delete(res_json);
    curl_easy_cleanup(handle);
    free(api_url);

    return shortlink;
}

void ShortLink_free(ShortLink *shortlink) {
    if (!shortlink)
        return;
    if (shortlink->url) {
        free(shortlink->url);
    }
    if (shortlink->_short) {
        free(shortlink->_short);
    }
    if (shortlink->href) {
        free(shortlink->href);
    }
    free(shortlink);
}
