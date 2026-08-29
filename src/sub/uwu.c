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
#include "subs.h"
#include "argparse.h"
#include "models/color.h"
#include "utils.h"


// No registration. uwu


// Helpers functions

static void
print_uwu(void)
;


int sub_uwu(const Arguments *args) {
    UNUSED(args);
    print_uwu();
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

