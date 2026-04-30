#include <stdio.h>
#include "subs.h"
#include "sub_meta.h"
#include "version.h"
#include "utils.h"


// Meta Register Function

void sub_register_version(void) {
    register_subcommand(
        (SubCommandMeta){
            .name = "version",
            .short_description = "Print version",
            .long_description = "Print HTMLify-CLI version",
            .options_count = 0
        },
        NULL
    );
}


int sub_version(const Arguments *args) {
    UNUSED(args);
    printf("HTMLify-CLI version %s\n", VERSION_STRING);
    return 0;
}
