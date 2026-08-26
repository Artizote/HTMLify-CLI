// String Data Structure

#pragma once

#include <stddef.h>

typedef struct str {
    char *value;
    size_t cap;
} str;


// Create and return new `string`
str *str_new(void);

// Initlize `string`
void str_init(str *str);

// Create new string with value `value`
str *str_create(const char *value);

// Set `str` value
void str_set(str *str, const char *chars);

// Unset `str` value
void str_unset(str *str);

// Append charectr array to `str`
void str_append(str *str, const char *chars);

// Adppend character to `str`
void str_append_char(str *str, char ch);

// Append `other` string to `self` string
void str_append_str(str *self, const str *other);

// Free `string`
void str_free(str *str);

