// Utils

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include "utils.h"
#include "config.h"
#include "data_structures/str.h"
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
    str *s = str_create("");
    int l = strlen(string);

    // escaping URL
    for (int i = 0; i < l; i++) {
        if (string[i] == ' ') {
            str_append(s, "%20");
        } else {
            str_append_char(s, string[i]);
        }
    }

    strlcat(url, s->value, URL_MAX_LEN);
    str_free(s);
}

static size_t callback_curl_string_append(void *buffer, size_t size, size_t nmemb, void *str) {
    str_append(str, buffer);
    return size * nmemb;
}

cJSON *curl_easy_perform_return_json(CURL *handle, CURLcode *res_code) {
    str *str = curl_easy_perform_return_string(handle, res_code);
    cJSON *json = cJSON_Parse(str->value);
    str_free(str);
    return json;
}

str *curl_easy_perform_return_string(CURL *handle, CURLcode *res_code) {
    str *str = str_create("");
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, callback_curl_string_append);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, str);
    *res_code = curl_easy_perform(handle);
    return str;
}

// Global flag for output styling
bool STYLING = true;

void disable_styling(void) {
    STYLING = false;
}

void enable_styling(void) {
    STYLING = true;
}

int printf_style(const char *fmt, ...) {
    if (!isatty(fileno(stdout))) return 0;
    if (!STYLING) return 0;
    int write_count;
    va_list args;
    va_start(args, fmt);
    write_count = vprintf(fmt, args);
    fflush(stdout);
    va_end(args);
    return write_count;
}

int printf_output(const char *fmt, ...) {
    int write_count;
    va_list args;
    va_start(args, fmt);
    write_count = vprintf(fmt, args);
    fflush(stdout);
    va_end(args);
    return write_count;
}

int printf_error(const char *fmt, ...) {
    int write_count;
    va_list args;
    va_start(args, fmt);
    write_count = vfprintf(stderr, fmt, args);
    fflush(stderr);
    va_end(args);
    return write_count;
}

int randint(int min, int max) {
    return min + rand() % (max - min + 1);
}

char *formate_size(size_t size) {
    char units[5][3] = {"B", "KB", "MB", "GB", "TB"};
    int degree = 0;
    double bytes = (double)size;
    for (; degree <= 5; degree++) {
        if (bytes < 1024) {
            break;
        }
        bytes /= 1024;
    }
    char *formated = malloc(9);
    snprintf(formated, 9, "%.2f %s", bytes, units[degree]);
    return formated;
}

