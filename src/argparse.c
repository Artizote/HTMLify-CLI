// Argument Parisng:

#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include "argparse.h"
#include "sub_meta.h"


Option *Option_new(void) {
    Option *option = calloc(1, sizeof(Option));
    option->values = NULL;
    return option;
}

void Option_init(Option *option, const char *name) {
    option->name = strdup(name);
}

Option *Option_create(const char *name) {
    Option *option = Option_new();
    Option_init(option, name);
    return option;
}

void Option_add_value(Option *option, const char *value) {
    option->value_count++;
    option->values = reallocarray(option->values, option->value_count, sizeof(char*));
    option->values[option->value_count-1] = strdup(value);
}

void Option_free(Option *option) {
    free(option->name);
    if (option->values) {
        for (int i=0; i<option->value_count; i++) {
            free(option->values[i]);
        }
        free(option->values);
    }
    free(option);
}


Arguments *Arguments_new(void) {
    Arguments *arguments = calloc(1, sizeof(Arguments));
    return arguments;
}

void Arguments_init(Arguments *args, int argc, char **argv) {
    Arguments_parse(args, argc, argv);
}

void Arguments_add_option(Arguments *args, Option *option) {
    args->option_count++;
    args->options = reallocarray(args->options, args->option_count, sizeof(Option));
    args->options[args->option_count-1] = option;
}

void Arguments_add_value(Arguments *args, char *value) {
    args->value_count++;
    args->values = reallocarray(args->values, args->value_count, sizeof(char*));
    args->values[args->value_count-1] = strdup(value);
}

void Arguments_add_option_value(Arguments *args, char *name, char *value) {
    Option *option = Arguments_get_option(args, name);
    if (!option) {
        return;
    }
    Option_add_value(option, value);
}

void Arguments_append_option_value(Arguments *args, char *value) {
    if (!args->option_count) {
        return;
    }
    Option_add_value(args->options[args->option_count-1], value);
}

Option *Arguments_get_option(const Arguments *args, const char *name) {
    if (!name && args->option_count) { // the first option ""
        return args->options[0];
    }
    for (int i = 0; i<args->option_count; i++) {
        if (strcmp(args->options[i]->name, name) == 0) {
            return args->options[i];
        }
    }
    return NULL;
}

char *Arguments_get_option_value(const Arguments *args, const char *name, int idx) {
    Option *option = Arguments_get_option(args, name);
    if (!option) {
        return NULL;
    }
    if (!option->value_count) {
        return NULL;
    }
    if (option->value_count <= idx) {
        return NULL;
    }
    return option->values[idx];
}

bool Arguments_has_option(const Arguments *args, const char *name) {
    if (!name || !args->option_count) {
        return false;
    }
    for (int i = 0; i<args->option_count; i++) {
        if (strcmp(args->options[i]->name, name) == 0) {
            return true;
        }
    }
    return false;
}

bool Arguments_is_subcommand(const Arguments *args, const char *sub) {
    if (!sub) {
        return false;
    }
    if (!args->subcommand) {
        return false;
    }
    return strcmp(args->subcommand, sub) == 0;
}

void Arguments_parse(Arguments *args, int argc, char **argv) {

    bool ignore_options = false;
    SubCommandOptionMeta *option_meta = NULL;

    for (int i=0; i<argc; i++) {
        char *arg = argv[i];

        // comman name
        if (i == 0) {
            args->command = strdup(arg);
            continue;
        }

        // subcommand name
        if (i == 1 && arg[0] != '-') {
            args->subcommand = strdup(arg);
            continue;
        }

        if (ignore_options) {
            Arguments_add_value(args, arg);
            continue;
        }

        // Ignore options flag
        if (strcmp(arg, "--") == 0) {
            ignore_options = true;
            continue;
        }

        // option
        if (arg[0] == '-') { // name

            // short option
            if (strlen(arg) > 1 && arg[1] != '-') {
                char buf[2];
                buf[1] = '\0';
                for (unsigned long j = 1; j<strlen(arg); j++) {
                    buf[0] = arg[j];
                    option_meta = get_subcommand_option_meta(args->subcommand, buf);
                    Option *s_option;
                    if (option_meta) {
                        s_option = Option_create(option_meta->name);
                    } else {
                        s_option = Option_create(buf);
                    }
                    Arguments_add_option(args, s_option);
                }
            }

            // long option
            if (strncmp(arg, "--", 2) == 0 && strlen(arg) > 2) {
                // removed the = checking and value asigning part, temporarly
                option_meta = get_subcommand_option_meta(args->subcommand, &arg[2]);
                Option *l_option;
                if (option_meta) {
                    l_option = Option_create(option_meta->name);
                } else {
                    l_option = Option_create(&arg[2]);
                }
                Arguments_add_option(args, l_option);
            }

            // ignoring - (maybe just for now)

        } else { // value
            if (option_meta) {
                Option *option = Arguments_get_option(args, option_meta->name);
                switch (option_meta->type) {
                    case ZERO_VALUE: {
                        Arguments_add_value(args, arg);
                        break;
                    }
                    case ONE_VALUE:
                    case ZERO_OR_ONE_VALUE: {
                        if (option->value_count < 1) {
                            Option_add_value(option, arg);
                        } else {
                            Arguments_add_value(args, arg);
                        }
                        break;
                    }
                    case ONE_OR_MORE_VALUE:
                    case ZERO_OR_MORE_VALUE: {
                        Option_add_value(option, arg);
                        break;
                    }
                }
            } else {
                if (args->option_count) {
                    Arguments_append_option_value(args, arg);
                } else {
                    Arguments_add_value(args, arg);
                }
            }
        }
    }
}

void Arguments_free(Arguments *args) {
    free(args->command);
    free(args->subcommand);
    for (int i=0; i<args->value_count; i++) {
        free(args->values[i]);
    }
    if (args->options) {
        for (int i = 0; i<args->option_count; i++) {
            Option_free(args->options[i]);
        }
        free(args->options);
    }
    free(args);
}

