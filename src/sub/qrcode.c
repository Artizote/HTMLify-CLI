// QR Code subcommand

#include <stdlib.h>
#include "subs.h"
#include "sub_meta.h"
#include "utils.h"
#include "characters.h"
#include "services/qrcode.h"
#include "models/color.h"


// Meta Register Function

void sub_register_qrcode(void) {
    register_subcommand(
        (SubCommandMeta){
            .name = "qrcode",
            .short_description = "Create and show QR Code",
            .long_description = "Create QR Code of givin data and show ASCII representations of it.",
            .options_count = 2
        }, (SubCommandOptionMeta[]){
            { .name="fg", .alias="f", .value="RRGGBB", .type=ONE_VALUE },
            { .name="bg", .alias="b", .value="RRGGBB", .type=ONE_VALUE },
        }
    );
}


int sub_qrcode(const Arguments *args) {
    if (!args->value_count) {
        printf_error("Provide data to encode in QR Code.\n");
        return 1;
    }

    QRCode *qrcode = QRCode_create(args->values[0]);
    if (!qrcode) {
        printf_error("Unable to create QR Code for provided data.\n");
        return 1;
    }

    bool has_fg_color, has_bg_color;
    Color *fg_color, *bg_color;
    char **qrcode_lines, *fg_color_hex, *bg_color_hex, *fg_color_escape_sequence, *bg_color_escape_sequence;
    int d, i, j, line_count;

    d = QRCode_get_dimention(qrcode);
    line_count = (d/2) + 1;

    has_fg_color = Arguments_has_option(args, "fg");
    has_bg_color = Arguments_has_option(args, "bg");

    if (has_fg_color) {
        fg_color_hex = Arguments_get_option_value(args,"fg", 0);
        fg_color = Color_create_from_hex(fg_color_hex);
        fg_color_escape_sequence = Color_to_fg_color_escape_sequence(fg_color);
    }

    if (has_bg_color) {
        bg_color_hex = Arguments_get_option_value(args,"bg", 0);
        bg_color = Color_create_from_hex(bg_color_hex);
        bg_color_escape_sequence = Color_to_bg_color_escape_sequence(bg_color);
    }

    qrcode_lines = QRCode_to_string_lines(qrcode);

    // Printing
    printf_style(CH_BLACK_SQUARE " QR Code\n");
    for (i = 0; i < line_count; i++) {
        if (i == 0) {
            printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL " ");
            for (j = 2; j < d+3; j++) {
                printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
            }
            printf_style(CH_BOX_DRAWINGS_LIGHT_DOWN_AND_LEFT);
            printf_style("\n");
        }
        printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL " ");

        if (has_fg_color) printf_style(fg_color_escape_sequence);
        if (has_bg_color) printf_style(bg_color_escape_sequence);

        printf_output("%s", qrcode_lines[i]);

        if (has_fg_color || has_bg_color) printf_style("\033[0m");

        printf_style(" " CH_BOX_DRAWINGS_LIGHT_VERTICAL);
        printf_output("\n");
        if (i == line_count - 1) {
            printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_RIGHT);
            for (j = 1; j < d+3; j++) {
                printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
            }
            printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_LEFT);
            printf_style("\n");
        }
    }

    if (has_fg_color) {
        Color_free(fg_color);
        free(fg_color_escape_sequence);
    }
    if (has_bg_color) {
        Color_free(bg_color);
        free(bg_color_escape_sequence);
    }
    for (i = 0; i < line_count; i++) {
        free(qrcode_lines[i]);
    }
    free(qrcode_lines);
    QRCode_free(qrcode);

    return 0;
}
