// Color Data Structure

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <data_structures/color.h>


Color *Color_new(void) {
    Color *color = malloc(sizeof(Color));
    return color;
}

void Color_init(Color *color, uint8_t r, uint8_t g, uint8_t b) {
    color->r = r;
    color->g = g;
    color->b = b;
}

void Color_init_from_hex(Color *color, const char *rgb) {
    if (!rgb) return;
    int l = strlen(rgb);
    if (l != 6 && l != 7) return;
    char *rgb_  = strdup(&rgb[l-6]);
    uint8_t r, g, b;
    sscanf(rgb_, "%02hhx%02hhx%02hhx", &r, &g, &b);
    Color_init(color, r, g, b);
    free(rgb_);
}

void Color_set(Color *color, uint8_t r, uint8_t g, uint8_t b) {
    color->r = r;
    color->g = g;
    color->b = b;
}

Color *Color_create(uint8_t r, uint8_t g, uint8_t b) {
    Color *color = Color_new();
    Color_init(color, r, g, b);
    return color;
}

Color *Color_create_from_hex(const char *rgb) {
    Color *color = Color_new();
    Color_init_from_hex(color, rgb);
    return color;
}

char *Color_to_formated_string(const Color *color, const char *fmt) {
    int max_len = 64, l;
    char *string = malloc(64+1);
    l = snprintf(string, max_len, fmt, color->r, color->g, color->b);
    string[l] = '\0';
    return string;
}

char *Color_to_string(const Color *color) {
    return Color_to_formated_string(color, "%02X%02X%02X");
}

char *Color_to_string_lower(const Color *color) {
    return Color_to_formated_string(color, "%02x%02x%02x");
}

char *Color_to_hex(const Color *color) {
    return Color_to_formated_string(color, "#%0X%0X%0X");
}

char *Color_to_fg_color_escape_sequence(const Color *color) {
    return Color_to_formated_string(color, "\033[38;2;%d;%d;%dm");
}

char *Color_to_bg_color_escape_sequence(const Color *color) {
    return Color_to_formated_string(color, "\033[48;2;%d;%d;%dm");
}

void Color_free(Color *color) {
    free(color);
}

