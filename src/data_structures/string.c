// String Data Structure

#include <malloc.h>
#include <string.h>
#include "data_structures/string.h"


string *string_new(void) {
    string *str = malloc(sizeof(string));
    return str;
}

void string_init(string *str) {
    str->value = malloc(1);
    str->value[0] = '\0';
    str->cap = 1;
}

string *string_create(const char *value) {
    string *str = string_new();
    string_init(str);
    string_append(str, value);
    return str;
}

void string_set(string *str, const char *chars) {
    size_t chars_len = strlen(chars);
    size_t require_cap = chars_len + str->cap + 1;
    if (require_cap > str->cap) {
        str->cap = require_cap + (str->cap * 1.5);
        str->value = realloc(str->value, str->cap);
    }
    strcpy(str->value, chars);
}

void string_unset(string *str) {
    str->value[0] = '\0';
}

void string_append(string *str, const char *chars) {
    size_t chars_len = strlen(chars);
    size_t require_cap = chars_len + str->cap + 1;
    if (require_cap > str->cap) {
        str->cap = require_cap + (str->cap * 1.5);
        str->value = realloc(str->value, str->cap);
    }
    strcat(str->value, chars);
}

void string_append_string(string *str, const string *other) {
    string_append(str, other->value); 
}

void string_free(string *str) {
    free(str->value);
    free(str);
}

