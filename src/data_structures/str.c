// String Data Structure

#include <malloc.h>
#include <string.h>
#include "data_structures/str.h"


str *str_new(void) {
    str *str = malloc(sizeof(struct str));
    return str;
}

void str_init(str *str) {
    str->value = malloc(1);
    str->value[0] = '\0';
    str->cap = 1;
}

str *str_create(const char *value) {
    str *str = str_new();
    str_init(str);
    str_append(str, value);
    return str;
}

void str_set(str *str, const char *chars) {
    size_t chars_len = strlen(chars);
    size_t require_cap = chars_len + str->cap + 1;
    if (require_cap > str->cap) {
        str->cap = require_cap + (str->cap * 1.5);
        str->value = realloc(str->value, str->cap);
    }
    strcpy(str->value, chars);
}

void str_unset(str *str) {
    str->value[0] = '\0';
}

void str_append(str *str, const char *chars) {
    size_t chars_len = strlen(chars);
    size_t require_cap = chars_len + str->cap + 1;
    if (require_cap > str->cap) {
        str->cap = require_cap + (str->cap * 1.5);
        str->value = realloc(str->value, str->cap);
    }
    strcat(str->value, chars);
}

void str_append_str(str *self, const str *other) {
    str_append(self, other->value); 
}

void str_free(str *str) {
    free(str->value);
    free(str);
}

