// String Data Structure

#pragma once

#include <stddef.h>

typedef struct string {
    char *value;
    size_t cap;
} string;


// Create and return new `string`
string *string_new(void);

// Initlize `string`
void string_init(string *string);

// Create new string with value `value`
string *string_create(const char *value);

// Set `string`
void string_set(string *string, const char *chars);

// Append charectr array to `string`
void string_append(string *string, const char *chars);

// Append `other` string to `self` string
void string_append_string(string *self, const string *other);

// Free `string`
void string_free(string *string);

