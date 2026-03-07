// Help Subcommand

#include <stdio.h>
#include "argparse.h"
#include "subs.h"
#include "ui.h"

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
