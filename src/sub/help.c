// Help Subcommand

#include <stdio.h>
#include "argparse.h"
#include "subs.h"

int sub_help(const Arguments *args) {
    printf("HTMLify CLI\n");
    printf("\n");

    printf("Usage:\n");
    printf("    %s [<options>] <subcommand> [<args>...]\n", args->command);
    printf("\n");

    printf("Options:\n");
    printf("    -h, --help      Show help\n");
    printf("\n");

    printf("Subcommands:\n");
    printf("    help            Show help\n");
    printf("\n");

    return 0;
}
