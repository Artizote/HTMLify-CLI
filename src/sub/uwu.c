// UwU subcommand

/*

 ▄▄    ▄▄            ▄▄    ▄▄ 
 ██    ██            ██    ██ 
 ██    ██ ██      ██ ██    ██ 
 ██    ██ ▀█  ██  █▀ ██    ██ 
 ██    ██  ██▄██▄██  ██    ██ 
 ▀██▄▄██▀  ▀██  ██▀  ▀██▄▄██▀ 
   ▀▀▀▀     ▀▀  ▀▀     ▀▀▀▀   
                              
*/

#include <stdlib.h>
#include <string.h>
#include "subs.h"
#include "argparse.h"
#include "models/color.h"
#include "utils.h"
#include "characters.h"


// No registration. Because it's secret. uwu


// Helpers functions

static void
print_uwu(void),
print_miku(void)
;


int sub_uwu(const Arguments *args) {
    UNUSED(args);
    int c = randint(0, 1);
    switch (c) {
        case 0: print_uwu();  break;
        case 1: print_miku(); break;
    }
    return 0;
}


void print_uwu(void) {
    Color colors[6] = {
        { 0xE2, 0xB4, 0xBD },
        { 0xBD, 0xB2, 0xFF },
        { 0xCF, 0xEC, 0xF3 },
        { 0xb3, 0xe7, 0xc6 },
        { 0xfb, 0xff, 0xdc },
        { 0xFE, 0xFD, 0x99 },
    };
    char *ces = Color_to_fg_color_escape_sequence(&colors[randint(0, 5)]);
    printf_output(
        "%s%s\033[0m",
        ces,
        "                              \n"
        " ▄▄    ▄▄            ▄▄    ▄▄ \n"
        " ██    ██            ██    ██ \n"
        " ██    ██ ██      ██ ██    ██ \n"
        " ██    ██ ▀█  ██  █▀ ██    ██ \n"
        " ██    ██  ██▄██▄██  ██    ██ \n"
        " ▀██▄▄██▀  ▀██  ██▀  ▀██▄▄██▀ \n"
        "   ▀▀▀▀     ▀▀  ▀▀     ▀▀▀▀   \n"
        "                              \n"
    );
    free(ces);
}

void print_miku(void) {
    char
    *c0 = "",
    *c1 = "000000",
    *c2 = "00bcd4",
    *c3 = "f50057",
    *c4 = "ffdccf",
    *c5 = "ffadb5",
    *c6 = "9e9e9e",
    *c7 = "ffffff"
    ;
    char *miku[20][27] = {
        { c0, c0, c0, c0, c0, c0, c1, c1, c1, c0, c0, c0, c0, c0, c0, c0, c0, c0, c1, c1, c1, c0, c0, c0, c0, c0, c0, },
        { c0, c0, c0, c0, c0, c1, c2, c2, c2, c1, c1, c1, c1, c1, c1, c1, c1, c1, c2, c2, c2, c1, c0, c0, c0, c0, c0, },
        { c0, c0, c0, c0, c1, c2, c2, c2, c1, c3, c1, c2, c2, c2, c2, c2, c1, c3, c1, c2, c2, c2, c1, c0, c0, c0, c0, },
        { c0, c0, c0, c1, c2, c2, c2, c1, c3, c1, c2, c2, c2, c2, c2, c2, c2, c1, c3, c1, c2, c2, c2, c1, c0, c0, c0, },
        { c0, c0, c0, c1, c2, c2, c1, c3, c1, c2, c2, c2, c2, c2, c2, c2, c2, c2, c1, c3, c1, c2, c2, c1, c0, c0, c0, },
        { c0, c0, c0, c1, c2, c1, c1, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c1, c1, c2, c1, c0, c0, c0, },
        { c0, c0, c0, c1, c2, c1, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c2, c1, c2, c1, c0, c0, c0, },
        { c0, c0, c1, c2, c2, c2, c2, c2, c2, c2, c2, c4, c2, c2, c2, c4, c2, c2, c2, c2, c2, c2, c2, c2, c1, c0, c0, },
        { c0, c0, c1, c2, c2, c2, c2, c2, c2, c2, c4, c4, c2, c2, c2, c4, c4, c2, c2, c2, c2, c2, c2, c2, c1, c0, c0, },
        { c0, c1, c2, c2, c2, c2, c1, c2, c2, c2, c1, c4, c4, c2, c2, c4, c1, c2, c2, c1, c1, c2, c2, c2, c2, c1, c0, },
        { c0, c1, c2, c2, c2, c2, c1, c2, c2, c2, c1, c4, c4, c4, c2, c4, c1, c2, c2, c2, c1, c2, c2, c2, c2, c1, c0, },
        { c0, c1, c2, c2, c2, c2, c1, c1, c2, c2, c2, c4, c4, c4, c4, c4, c2, c2, c2, c1, c1, c2, c2, c2, c2, c1, c0, },
        { c1, c2, c2, c2, c2, c1, c0, c0, c1, c2, c5, c4, c4, c4, c4, c4, c5, c2, c1, c0, c0, c1, c2, c2, c2, c2, c1, },
        { c1, c2, c2, c2, c2, c1, c0, c0, c0, c1, c1, c1, c4, c1, c4, c1, c1, c1, c0, c0, c0, c1, c2, c2, c2, c2, c1, },
        { c1, c2, c2, c2, c2, c1, c0, c0, c0, c0, c0, c1, c1, c2, c1, c1, c0, c0, c0, c0, c0, c1, c2, c2, c2, c2, c1, },
        { c1, c2, c2, c2, c2, c1, c0, c0, c0, c0, c1, c1, c6, c2, c6, c1, c1, c0, c0, c0, c0, c1, c2, c2, c2, c2, c1, },
        { c1, c2, c2, c2, c2, c1, c0, c0, c0, c0, c1, c7, c6, c2, c6, c7, c1, c0, c0, c0, c0, c1, c2, c2, c2, c2, c1, },
        { c1, c2, c2, c2, c2, c2, c1, c0, c0, c0, c1, c1, c2, c1, c2, c1, c1, c0, c0, c0, c1, c2, c2, c2, c2, c2, c1, },
        { c0, c1, c2, c2, c2, c2, c2, c1, c0, c0, c0, c1, c1, c1, c1, c1, c0, c0, c0, c1, c2, c2, c2, c2, c2, c1, c0, },
        { c0, c0, c1, c1, c1, c1, c1, c0, c0, c0, c0, c0, c0, c0, c0, c0, c0, c0, c0, c0, c1, c1, c1, c1, c1, c0, c0, },
    };
    int i, j, w = 27, h = 20;
    Color *color = Color_new();
    char *uc, *dc, *ch, *ts;
    for (i = 0; i < h; i+=2) {
        for (j = 0; j < w; j++) {
            uc = miku[i][j];
            dc = miku[i+1][j];
            if (!strlen(uc) && !strlen(dc)) {
                ch = " ";
            }
            if (strlen(uc) && !strlen(dc)) {
                ch = CH_UPPER_HALF_BLOCK;
                Color_init_from_hex(color, uc);
                ts = Color_to_fg_color_escape_sequence(color);
                printf_output(ts);
                free(ts);
            }
            if (!strlen(uc) && strlen(dc)) {
                ch = CH_LOWER_HALF_BLOCK;
                Color_init_from_hex(color, dc);
                ts = Color_to_fg_color_escape_sequence(color);
                printf_output(ts);
                free(ts);
            }
            if (strlen(uc) && strlen(dc)) {
                ch = CH_UPPER_HALF_BLOCK;
                Color_init_from_hex(color, uc);
                ts = Color_to_fg_color_escape_sequence(color);
                printf_output(ts);
                free(ts);
                Color_init_from_hex(color, dc);
                ts = Color_to_bg_color_escape_sequence(color);
                printf_output(ts);
                free(ts);
            }
            printf_output("%s\033[0m", ch);
        }
        printf_output("\n");
    }
    printf_output("\n");
    Color_free(color);
}

