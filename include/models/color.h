// Color Data Structure

#pragma once

#include <stdint.h>


typedef struct {
    uint8_t r, g, b;
} Color;


// Create new `Color` struct
Color *Color_new(void);

// Initlize `color`
void Color_init(Color *color, uint8_t r, uint8_t g, uint8_t b);

// Initlize `color` with hex (e.g. #1234ff, aaeedd, AaFe2a)
void Color_init_from_hex(Color *color, const char *rgb);

// Set values of `color`
void Color_set(Color *color, uint8_t r, uint8_t g, uint8_t b);

// Create new `Color` with values
Color *Color_create(uint8_t r, uint8_t g, uint8_t b);

// Create `Color` from hex (e.g. #1234ff, aaeedd, AaFe2a)
Color *Color_create_from_hex(const char *rgb);

// Return string with values of `color` as `fmt` format specified
char *Color_to_formated_string(const Color *color, const char *fmt);

// Return color string with Color representation in RRGGBB (with #) format
char *Color_to_string(const Color *color);

// Same as Color_to_string, but in lower case
char *Color_to_string_lower(const Color *color);

// Return color string with Color representation in #RRGGBB format
char *Color_to_hex(const Color *color);

// Return color as string for escape sequnce to change foreground color
char *Color_to_fg_color_escape_sequence(const Color *color);

// Return color as string for escape sequnce to change background color
char *Color_to_bg_color_escape_sequence(const Color *color);

// Free the `Color` struct
void Color_free(Color *color);

