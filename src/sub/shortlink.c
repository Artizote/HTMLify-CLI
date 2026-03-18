// ShortLink subcommand

#include <stdio.h>
#include <stdbool.h>
#include "subs.h"
#include "argparse.h"
#include "services/shortlink.h"
#include "characters.h"
#include "utils.h"


// helper functions

static inline void
    print_input_line_style(void),
    print_last_input_line_style(void),
    print_output_line_style(void),
    print_last_output_line_style(void)
;


int sub_shortlink(const Arguments *args) {
    int ret_code = 0;

    printf_style(CH_BLACK_SQUARE " ShortLink\n");

    if (!args->option_count) {
        printf_style(CH_BOX_DRAWINGS_LIGHT_ARC_UP_AND_RIGHT CH_BLACK_RIGHT_POINTING_TRIANGLE " ");
        printf_error("Provide URL to create shortlink or lookup by id or short\n");
        ret_code = 0;
        return ret_code;
    }

    bool flag_new = Arguments_has_option(args, "n");

    if (Arguments_has_option(args, "")) { // short the url(s)
        Option *urls = Arguments_get_option(args, "");
        for (int i = 0; i < urls->value_count; i++) {

            // input line style
            if (!(i == urls->value_count - 1)) {
                print_input_line_style();
            } else {
                print_last_input_line_style();
            }

            char *url_to_short = urls->values[i];
            printf_style("%s\n", url_to_short);
            ShortLink *shortlink = ShortLink_create(url_to_short, flag_new);

            // output line style
            if (!(i == urls->value_count - 1)) {
                print_output_line_style();
            } else {
                print_last_output_line_style();
            }

            if (!shortlink) {
                printf_error("Unable to short this url. ");
                printf_output("\n");
                ret_code = 1;
            } else {
                printf_output("%s\n", shortlink->url);
            }

            ShortLink_free(shortlink);
        }
        return ret_code;
    }

    if (Arguments_has_option(args, "id")) { // lookup short url by id
        Option *ids = Arguments_get_option(args, "id");
        if (!ids->value_count) {
            printf_style(CH_BOX_DRAWINGS_LIGHT_ARC_UP_AND_RIGHT CH_BLACK_RIGHT_POINTING_TRIANGLE " ");
            printf_error("provide id(s) to lookup\n");
            return ret_code;
        }
        for (int i = 0; i < ids->value_count; i++) {
            int id_to_lookup;
            sscanf(ids->values[i], "%d", &id_to_lookup);

            // input line style
            if (!(i == ids->value_count - 1)) {
                print_input_line_style();
            } else {
                print_last_input_line_style();
            }

            printf_style("%d\n", id_to_lookup);
            ShortLink *shortlink = ShortLink_get_by_id(id_to_lookup);

            // output line style
            if (!(i == ids->value_count - 1)) {
                print_output_line_style();
            } else {
                print_last_output_line_style();
            }

            if (!shortlink) {
                printf_error("ShortLink not found with this id");
                printf_output("\n");
            } else {
                printf_output("%s\n", shortlink->url);
            }

            ShortLink_free(shortlink);
        }
        return ret_code;
    }

    if (Arguments_has_option(args, "short")) { // lookup short urls by shorts
        Option *shorts = Arguments_get_option(args, "short");
        if (!shorts->value_count) {
            fprintf(stderr, "provide short(s) to lookup\n");
            return ret_code;
        }
        for (int i = 0; i < shorts->value_count; i++) {
            char *_short = shorts->values[i];

            // input line style
            if (!(i == shorts->value_count - 1)) {
                print_input_line_style();
            } else {
                print_last_output_line_style();
            }

            ShortLink *shortlink = ShortLink_get_by_short(_short);

            // output line style
            if (!(i == shorts->value_count - 1)) {
                print_output_line_style();
            } else {
                print_last_output_line_style();
            }

            if (!shortlink) {
                fprintf(stderr, "ShortLink not found with this short\n");
            } else {
                printf("%s\n", shortlink->url);
            }

            ShortLink_free(shortlink);
        }
        return ret_code;
    }

    return ret_code;
}


static inline void print_input_line_style(void) {
    printf_style(
        CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_RIGHT
        CH_BOX_DRAWINGS_LIGHT_DOWN_AND_HORIZONTAL
        CH_BOX_DRAWINGS_LIGHT_HORIZONTAL
        " "
    );
}

static inline void print_last_input_line_style(void) {
    printf_style(
        CH_BOX_DRAWINGS_LIGHT_ARC_UP_AND_RIGHT
        CH_BOX_DRAWINGS_LIGHT_DOWN_AND_HORIZONTAL
        CH_BOX_DRAWINGS_LIGHT_HORIZONTAL
        " "
    );
}

static inline void print_output_line_style(void) {
    printf_style(
        CH_BOX_DRAWINGS_LIGHT_VERTICAL
        CH_BOX_DRAWINGS_LIGHT_ARC_UP_AND_RIGHT
        CH_BLACK_RIGHT_POINTING_TRIANGLE
        " "
    );
}

static inline void print_last_output_line_style(void) {
    printf_style(
        " "
        CH_BOX_DRAWINGS_LIGHT_ARC_UP_AND_RIGHT
        CH_BLACK_RIGHT_POINTING_TRIANGLE
        " "
    );
}

