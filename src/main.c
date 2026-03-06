#include <stdio.h>
#include "argparse.h"
#include "subs.h"

int main(int argc, char **argv) {
    Arguments *args = Arguments_init(argc, argv);

    if (args->subcommand) {
        if (Arguments_is_subcommand(args, "help")) {
            return sub_help(args);
        } if (Arguments_is_subcommand(args, "version")) {
            return sub_version(args);
        } else {
            printf("%s: '%s' subcommand not found, try '%s help'.\n", args->command, args->subcommand, args->command);
        }
    } else if (args->option_count) {
        if (Arguments_has_option(args, "h") || Arguments_has_option(args, "help")) {
            return sub_help(args);
        } if (Arguments_has_option(args, "v") || Arguments_has_option(args, "version")) {
            return sub_version(args);
        } else {
            printf("%s: not a valid option, try `%s help'.\n", args->command, args->command);
        }
    } else {
        return sub_help(args);
    }

    return 0;
}
