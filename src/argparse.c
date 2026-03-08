// Argument Parisng:

#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include "argparse.h"


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

void Arguments_append_option_value(Arguments *args, char *value) {
    if (!args->option_count) {
        Option *option = Option_create("");
        Arguments_add_option(args, option);
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

        // option
        if (arg[0] == '-') { // name

            // short option
            if (strlen(arg) > 1 && arg[1] != '-') {
                char buf[2];
                buf[1] = '\0';
                for (unsigned long j = 1; j<strlen(arg); j++) {
                    buf[0] = arg[j];
                    Option *s_option = Option_create(buf);
                    Arguments_add_option(args, s_option);
                }
            }

            // long option
            if (strncmp(arg, "--", 2) == 0 && strlen(arg) > 2) {
                char *los = &arg[2];
                char *equal = strchr(los, '=');
                if (equal != NULL) {
                    equal[0] = '\0';
                    char *value = ++equal;
                    Option *l_option = Option_create(los);
                    if (value) {
                        Option_add_value(l_option, value);
                    }
                    Arguments_add_option(args, l_option);
                } else {
                    Option *l_option = Option_create(&arg[2]);
                    Arguments_add_option(args, l_option);
                }
            }

            // ignoring - and -- (maybe just for now)

        } else { // value
            Arguments_append_option_value(args, arg);
        }
    }
}

void Arguments_free(Arguments *args) {
    free(args->command);
    free(args->subcommand);
    if (args->options) {
        for (int i = 0; i<args->option_count; i++) {
            Option_free(args->options[i]);
        }
        free(args->options);
    }
    free(args);
}

