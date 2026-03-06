#include <stdio.h>
#include "subs.h"
#include "version.h"

int sub_version(const Arguments *args) {
    printf("HTMLify-CLI version %s\n", VERSION_STRING);
    return 0;
}
