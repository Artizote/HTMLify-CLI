// Help Subcommand

#include <stdio.h>
#include "argparse.h"
#include "subs.h"
#include "sub_meta.h"
#include "ui.h"


// Meto Register Function

void sub_register_help(void) {
    register_subcommand(
        (SubCommandMeta){
            .name = "help",
            .short_description = "Print help",
            .options_count = 0,
        },
        NULL
    );
}


int sub_help(const Arguments *args) {
    print_banner_with_version();
    printf("\n");

    printf("Usage:\n");
    printf("    %s [options]\n", args->command);
    printf("    %s <subcommand> [options] [args...]\n", args->command);

    printf("\n");

    printf("Options:\n");
    printf("    -h, --help      Show help\n");
    printf("    -v, --version   Show version\n");
    printf("\n");

    printf("Subcommands:\n");
    printf("    help            Show help\n");
    printf("    version         Show version\n");
    printf("\n");

    return 0;
}
