// Utils

#pragma once

#include "data_structures/str.h"
#include "curl/curl.h"
#include "cJSON.h"


// Macro to remove warngis
// regarding unused function arguments
#define UNUSED(x) (void)(x)

#define URL_MAX_LEN 2048


// make URL string based DEFAULT_API_VERSION and `endpoint`
char *make_api_url(const char *endpoint);

// make URL string based on `v` (version) and `endpoint`
char *make_api_url_with_version(int v, const char *endpoint);

// append string to url
void append_string_to_url(char *url, const char *string);

// perfrom the curl request and populate `json` from response JSON
cJSON *curl_easy_perform_return_json(CURL *handle, CURLcode *res_code);

// perform the curl request and populate `string` from the response
str *curl_easy_perform_return_string(CURL *handle, CURLcode *res_code);

// disabel styling for output
void disable_styling(void);

// enable styling for output
void enable_styling(void);

// for printing strings which are not the actuall output, but the styling
int printf_style(const char *fmt, ...);

// for printing strings which are output
int printf_output(const char *fmt, ...);

// for printing error messages
int printf_error(const char *fmt, ...);

// random int in range [a, b], including both end points.
int randint(int min, int max);

