// Main Command

#include <stdio.h>
#include "argparse.h"
#include "subs.h"
#include "sub_meta.h"


// Meta Register Fonction

void sub_register_main(void) {
    register_subcommand(
        (SubCommandMeta){
            .name = "",
            .short_description = "",
            .options_count = 3,
        }, (SubCommandOptionMeta[]){
            { .name="help", .alias="h" },
            { .name="version", .alias="v" },
            { .name="print-config", .alias="c" },
        }
    );
}


int sub_main(const Arguments *args) {
    if (Arguments_has_option(args, "h") || Arguments_has_option(args, "help")) {
        return sub_help(args);
    }
    if (Arguments_has_option(args, "v") || Arguments_has_option(args, "version")) {
        return sub_version(args);
    }
    if (Arguments_has_option(args, "c") || Arguments_has_option(args, "print-config")) {
        return sub_print_config(args);
    }
    printf("%s: unrecognizable options, try '%s help'.\n", args->command, args->command);
    return 0;
}
