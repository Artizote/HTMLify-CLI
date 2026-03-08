////////////////////
// ┓┏┏┳┓┳┳┓┓ •┏   //
// ┣┫ ┃ ┃┃┃┃ ┓╋┓┏ //
// ┛┗ ┻ ┛ ┗┗┛┗┛┗┫ //
// ◼            ┛ //
////////////////////

#include "argparse.h"
#include "command_handler.h"

int main(int argc, char **argv) {
    Arguments *args = Arguments_new();
    Arguments_init(args, argc, argv);
    int return_code = command_handler(args);
    Arguments_free(args);
    return return_code;
}
