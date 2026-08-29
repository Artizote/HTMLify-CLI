// Command Handler

#include <stdio.h>
#include "argparse.h"
#include "subs.h"


/*
 * Command Handling flow
 *
 *  command subcommand --option values values...
 *      - all args will be passed to the currusponding subcommand to handle
 *      - if no subcommand match with the name, error message will be shown
 *
 *  command --option value value...
 *      - will pass the arguments to `sub_main` to handle
 *      - were it will check for currosponding subcommand for option, like --help for help
 *        and fire that subcommand
 *      - if no associtade subcommand found, error message will be shown
 *
 *  command
 *      - about subcommand will be triggered
 *      - about subcommand is not available, so help subcommand is got triggered
 *
 *
 * all subcommand are supposed to return status code, which will be returned by
 * command_handler too, for the main function
 * 
 */
 

int command_handler(Arguments *args) {
    // If subcomand passed
    if (args->subcommand) {
        if (Arguments_is_subcommand(args, "help")) {
            return sub_help(args);
        }
        if (Arguments_is_subcommand(args, "version")) {
            return sub_version(args);
        }
        if (Arguments_is_subcommand(args, "shortlink")) {
            return sub_shortlink(args);
        }
        if (Arguments_is_subcommand(args, "print-config")) {
            return sub_print_config(args);
        }
        if (Arguments_is_subcommand(args, "qrcode")) {
            return sub_qrcode(args);
        }
        if (Arguments_is_subcommand(args, "uwu")) {
            return sub_uwu(args);
        }
        printf("%s: '%s' subcommand not found, try '%s help'.\n", args->command, args->subcommand, args->command);
    // If options passed
    } else if (args->option_count) {
        sub_main(args);
    // If only command is passed
    } else {
        // about command is not available,
        return sub_help(args);
    }

    return 0;
}
