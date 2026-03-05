// Argument Parsing

#pragma once

typedef struct Option {
    char *name;
    int value_count;
    char **values;
} Option;

typedef struct Arguments {
    char *command;
    char *subcommand;
    int option_count;
    Option **options;
} Arguments;


// Create and return `Option` struct pointer
Option *Option_new(void);

// Initialize a new Option structure with the given name
Option *Option_init(char *name);

// Add `value` to `option`
void Option_add_value(Option *option, char *value);

// Free the `option` memory
void Option_free(Option *option);


// Cretae and return `Arguments` struct pointer
Arguments *Arguments_new(void);

// Initialize a new `Arguments` and return pointer
Arguments *Arguments_init(int argc, char **argv);

// Add `option` to `arguments`
void Arguments_add_option(Arguments *arguments, Option *option);

// Add `value` to last option of `arguments`, create unnamed option if found
void Arguments_append_option_value(Arguments *arguments, char *value);

// Get `option` from `arguments` by name
Option *Arguments_get_option(Arguments *arguments, char *name);

// Get value on index `idx` of option with name `name` from `arguments`, return NULL if not found
char *Argument_get_option_value(Arguments *arguments, char*name, int idx);

// Parse command line arguments and update to the `arguments`
void Arguments_parse(Arguments *arguments, int argc, char **argv);

// Free the `arguments` memory
void Arguments_free(Arguments *arguments);

