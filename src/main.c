#include <stdio.h>
#include <string.h>
#include "argparse.h"
#include "subs.h"

int main(int argc, char **argv) {
    Arguments *args = Arguments_init(argc, argv);

    if (args->subcommand) {
        if (strcmp(args->subcommand, "help") == 0) {
            sub_help(args);
        } else {
            printf("%s: '%s' subcommand not found, try '%s help'.\n", args->command, args->subcommand, args->command);
        }
    } else if (args->option_count) {
        if (Arguments_has_option(args, "h") || Arguments_has_option(args, "help")) {
            sub_help(args);
        } else {
            printf("%s: not a valid option, try `%s help'.\n", args->command, args->command);
        }
    } else {
        sub_help(args);
    }

    return 0;
}
