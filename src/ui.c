// UI

#include <stdio.h>
#include "ui.h"
#include "version.h"


void print_banner(void) {
    printf("┓┏┏┳┓┳┳┓┓ •┏  \n");
    printf("┣┫ ┃ ┃┃┃┃ ┓╋┓┏\n");
    printf("┛┗ ┻ ┛ ┗┗┛┗┛┗┫\n");
    printf("◼            ┛\n");
}

void print_banner_with_version(void) {
    printf("┓┏┏┳┓┳┳┓┓ •┏  \n");
    printf("┣┫ ┃ ┃┃┃┃ ┓╋┓┏\n");
    printf("┛┗ ┻ ┛ ┗┗┛┗┛┗┫\n");
    printf("◼ %s ┛\n", VERSION_STRING);
}
