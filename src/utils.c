// Utils

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "utils.h"
#include "config.h"
#include "data_structures/string.h"
#include "cJSON.h"
#include "curl/curl.h"


char *make_api_url(const char *endpoint) {
    return make_api_url_with_version(DEFAULT_API_VERSION, endpoint);
}

char *make_api_url_with_version(int v, const char *endpoint) {
    char *url = malloc(URL_MAX_LEN);
    if (v) {
        sprintf(url, "%s/v%d%s", API_URL_BASE, v, endpoint);
    } else {
        sprintf(url, "%s%s", API_URL_BASE, endpoint);
    }
    return url;
}

void append_string_to_url(char *url, const char *string) {
    strlcat(url, string, URL_MAX_LEN);
}

static size_t callback_curl_string_append(void *buffer, size_t size, size_t nmemb, void *str) {
    string_append(str, buffer);
    return size * nmemb;
}

cJSON *curl_easy_perform_return_json(CURL *handle, CURLcode *res_code) {
    string *str = curl_easy_perform_return_string(handle, res_code);
    cJSON *json = cJSON_Parse(str->value);
    string_free(str);
    return json;
}

string *curl_easy_perform_return_string(CURL *handle, CURLcode *res_code) {
    string *str = string_create("");
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, callback_curl_string_append);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, str);
    *res_code = curl_easy_perform(handle);
    return str;
}

