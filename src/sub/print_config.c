#include <stdio.h>
#include <string.h>
#include "subs.h"
#include "sub_meta.h"
#include "utils.h"
#include "config.h"
#include "version.h"
#include "characters.h"


// Meta Register Function

void sub_register_print_config(void) {
    register_subcommand(
        (SubCommandMeta){
            .name = "print-config",
            .short_description = "Print Config Variables",
            .long_description = "Print Config Variables",
            .options_count = 0
        },
        NULL
    );
}


// Helper functions
int calculate_padding(int len);
static inline void
    print_first_row_seperator(int name_padding, int value_padding),
    print_row_separator(int name_padding, int value_padding),
    print_last_row_seperator(int name_padding, int value_padding),
    print_row_data(int name_padding, char *name, int value_padding, char *value)
;


int sub_print_config(const Arguments *args) {
    UNUSED(args);
    #ifdef DEV_ENV
        char *build_type = "Development";
    #endif 
    #ifdef PROD_ENV
        char *build_type = "Production";
    #endif

    char *api_url_base = API_URL_BASE;
    char *version_string = VERSION_STRING;

    unsigned long max_name_len = 14; // len of longest name (VERSION_STRING)
    unsigned long max_value_len = strlen(build_type);
    if (strlen(api_url_base) > max_value_len)
        max_value_len = strlen(api_url_base);
    if (strlen(version_string) > max_value_len)
        max_value_len = strlen(version_string);

    int name_padding = calculate_padding(max_name_len);
    int value_padding = calculate_padding(max_value_len);

    printf_style(CH_BLACK_SQUARE " Configs\n");
    print_first_row_seperator(name_padding, value_padding);
    print_row_data(name_padding, "BUILD_TYPE", value_padding, build_type);
    print_row_separator(name_padding, value_padding);
    print_row_data(name_padding, "API_URL_BASE", value_padding, API_URL_BASE);
    print_row_separator(name_padding, value_padding);
    print_row_data(name_padding, "VERSION_STRING", value_padding, version_string);
    print_last_row_seperator(name_padding, value_padding);

    return 0;
}


int calculate_padding(int len) {
    len++;
    while (len % 4)
        len++;
    return len;
}

static inline void print_first_row_seperator(int name_padding, int value_padding) {
    int i;
    printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_RIGHT);
    for (i=0; i<name_padding+2; i++)
        printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
    printf_style(CH_BOX_DRAWINGS_LIGHT_DOWN_AND_HORIZONTAL);
    for (i=0; i<value_padding+2; i++)
        printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
    printf_style(CH_BOX_DRAWINGS_LIGHT_DOWN_AND_LEFT);
    printf_style("\n");
}

static inline void print_row_separator(int name_padding, int value_padding) {
    int i;
    printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_RIGHT);
    for (i=0; i<name_padding+2; i++)
        printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
    printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_HORIZANTAL);
    for (i=0; i<value_padding+2; i++)
        printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
    printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_LEFT);
    printf_style("\n");
}

static inline void print_last_row_seperator(int name_padding, int value_padding) {
    int i;
    printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_RIGHT);
    for (i=0; i<name_padding+2; i++)
        printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
    printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_HORIZONTAL);
    for (i=0; i<value_padding+2; i++)
        printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
    printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_LEFT);
    printf_style("\n");
}

static inline void print_row_data(int name_padding, char *name, int value_padding, char *value) {
    printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL " ");
    printf_output("%*s", -name_padding, name);
    printf_style(" " CH_BOX_DRAWINGS_LIGHT_VERTICAL " ");
    printf_output("%*s", -value_padding, value);
    printf_style(" " CH_BOX_DRAWINGS_LIGHT_VERTICAL);
    printf_output("\n");
}

