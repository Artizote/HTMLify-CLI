// Help Subcommand

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argparse.h"
#include "subs.h"
#include "sub_meta.h"
#include "ui.h"
#include "characters.h"
#include "utils.h"


#define lb print_left_border()


// Meta Register Function

void sub_register_help(void) {
    register_subcommand(
        (SubCommandMeta){
            .name = "help",
            .short_description = "Shows help",
            .long_description = "Shows help for HTMLify-CLI or for available subcommands.",
            .options_count = 0,
        },
        NULL
    );
}

// Helpers
static void
    print_subcommand_line(SubCommandMeta *subcommand_meta, int second_column_padding),
    print_option_line(SubCommandOptionMeta *option_meta, int second_column_padding),
    print_left_border(void)
;


int sub_help(const Arguments *args) {
    int second_column_padding = 22;

    if (!args->value_count) {
        print_banner_with_version();
        lb; printf("\n");

        // Usage of `sub_main`
        lb; printf("Usage:\n");
        lb; printf("    %s [options]\n", args->command);
        lb; printf("    %s <subcommand> [options] [args...]\n", args->command);
        lb; printf("\n");

        // Options of `sub_main`
        SubCommandMeta *sub_main_meta = get_subcommand_meta("");
        lb; printf("Options:\n");
        for (int i = 0; i < sub_main_meta->options_count; i++) {
            print_option_line(&sub_main_meta->options[i], second_column_padding);
        }
        lb; printf("\n");

        // Subcommands
        char **command_names = get_subcommand_names();
        int command_count = get_subcommand_count();
        lb; printf("Subcommands:\n");
        for (int i = 0; i < command_count; i++) {
            print_subcommand_line(get_subcommand_meta(command_names[i]), second_column_padding);
            free(command_names[i]);
        }
        lb; printf("\n");
        free(command_names);
        return 0;
    }

    // Help for subcommand

    printf_style(CH_BLACK_SQUARE " Help\n");

    SubCommandMeta *subcommand_meta = get_subcommand_meta(Arguments_get_value(args, 0));
    if (!subcommand_meta) {
        lb; printf_error("No help found, try %s help to list all subcommands.\n", args->command);
        return 0;
    }

    lb; printf("\n");
    lb; printf("    subcommand: %s\n", subcommand_meta->name);
    lb; printf("\n");
    if (subcommand_meta->long_description) {
        lb; printf("    %s\n", subcommand_meta->long_description);
    } else {
        lb; printf("    %s\n", subcommand_meta->short_description);
    }
    lb; printf("\n");

    // Usage
    lb; printf("Usage:\n");
    // we don't have any clue if subcommand accepts operants/arggumens or not
    lb; printf("    %s %s [args...]\n", args->command, subcommand_meta->name);
    if (subcommand_meta->options_count) {
        lb; printf("    %s %s [options] [args...]\n", args->command, subcommand_meta->name);
    }
    lb; printf("\n");

    // Options
    if (subcommand_meta->options_count) {
        lb; printf("Options:\n");
        for (int i = 0; i < subcommand_meta->options_count; i++) {
            print_option_line(&subcommand_meta->options[i], second_column_padding);
        }
        lb; printf("\n");
    }

    return 0;
}


static void print_subcommand_line(SubCommandMeta *subcommand_meta, int second_column_padding) {
    if (strcmp(subcommand_meta->name, "") == 0) {
        return;
    }
    lb;
    int printed = printf("    %s", subcommand_meta->name);
    for (int j = 0; j < second_column_padding - printed; j++) {
        printf(" ");
    }
    printf("%s\n", subcommand_meta->short_description);
}

static void print_option_line(SubCommandOptionMeta *option_meta, int second_column_padding) {
    lb;
    int printed = 0;
    printed += printf("    ");
    if (option_meta->alias && strlen(option_meta->alias) > 0) {
        printed += printf("-%s, ", option_meta->alias);
    }
    printed += printf("--%s", option_meta->name);
    if (option_meta->value && strlen(option_meta->value) > 0) {
        for (int j = 0; j < second_column_padding - printed; j++) {
            printf(" ");
        }
        switch (option_meta->type) {
            case ZERO_VALUE: {
                break;
            }
            case ZERO_OR_ONE_VALUE: {
                printf("[%s]", option_meta->value);
                break;
            }
            case ZERO_OR_MORE_VALUE: {
                printf("[%s ...]", option_meta->value);
                break;
            }
            case ONE_VALUE: {
                printf("%s", option_meta->value);
                break;
            }
            case ONE_OR_MORE_VALUE: {
                printf("%s [...]", option_meta->value);
                break;
            }
        }
    }
    printf("\n");
}

static void print_left_border(void) {
    printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL " ");
}

#undef lb
