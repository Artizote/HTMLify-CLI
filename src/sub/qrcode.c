// QR Code subcommand

#include <stdlib.h>
#include "subs.h"
#include "sub_meta.h"
#include "utils.h"
#include "characters.h"
#include "services/qrcode.h"


// Meta Register Function

void sub_register_qrcode(void) {
    register_subcommand(
        (SubCommandMeta){
            .name = "qrcode",
            .short_description = "Create and show QR Code",
            .long_description = "Create QR Code of givin data and show ASCII representations of it.",
            .options_count = 0
        },
        NULL
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

    char **qrcode_lines = QRCode_to_string_lines(qrcode);
    int d = QRCode_get_dimention(qrcode);
    int i, j, line_count = d/2+1;

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
        printf_output("%s", qrcode_lines[i]);
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

    free(qrcode_lines);
    QRCode_free(qrcode);

    return 0;
}
