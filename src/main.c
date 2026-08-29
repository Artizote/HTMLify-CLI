////////////////////
// ┓┏┏┳┓┳┳┓┓ •┏   //
// ┣┫ ┃ ┃┃┃┃ ┓╋┓┏ //
// ┛┗ ┻ ┛ ┗┗┛┗┛┗┫ //
// ◼            ┛ //
////////////////////

#include <stdlib.h>
#include <time.h>
#include "argparse.h"
#include "command_handler.h"
#include "sub_meta.h"


int main(int argc, char **argv) {
    srand(time(NULL));
    register_subcommands();
    Arguments *args = Arguments_new();
    Arguments_init(args, argc, argv);
    int return_code = command_handler(args);
    Arguments_free(args);
    clean_subcommand_registry();
    return return_code;
}
