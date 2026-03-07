////////////////////
// ┓┏┏┳┓┳┳┓┓ •┏   //
// ┣┫ ┃ ┃┃┃┃ ┓╋┓┏ //
// ┛┗ ┻ ┛ ┗┗┛┗┛┗┫ //
// ◼            ┛ //
////////////////////

#include "argparse.h"
#include "command_handler.h"

int main(int argc, char **argv) {
    Arguments *args = Arguments_init(argc, argv);
    int return_code = command_handler(args);
    return return_code;
}
