// Argument Parsing

#pragma once

#include <stdbool.h>


typedef struct Option {
    char *name;
    int value_count;
    char **values;
} Option;

typedef struct Arguments {
    char *command;
    char *subcommand;
    int value_count;
    char **values;
    int option_count;
    Option **options;
} Arguments;


// Create and return `Option` struct pointer
Option *Option_new(void);

// Initialize a `option`
void Option_init(Option *option, const char *name);

// Create new `Option` with `name` and return
Option *Option_create(const char *name);

// Add `value` to `option`
void Option_add_value(Option *option, const char *value);

// Free the `option` memory
void Option_free(Option *option);


// Cretae and return `Arguments` struct pointer
Arguments *Arguments_new(void);

// Initialize `args` 
void Arguments_init(Arguments *arguments, int argc, char **argv);

// Add `option` to `arguments`
void Arguments_add_option(Arguments *arguments, Option *option);

// Add `value` in last of values of `arguments`
void Arguments_add_value(Arguments *arguments, char *value);

// Add `value` to the Option with name `name` in `arguments`
void Arguments_add_option_value(Arguments *arguments, char *name, char *value);

// Add `value` to last option of `arguments`, create unnamed option if found
void Arguments_append_option_value(Arguments *arguments, char *value);

// Get value on index `idx` in `arguments`, return NULL if not found
char *Arguments_get_value(const Arguments *arguments, int idx);

// Get `option` from `arguments` by name
Option *Arguments_get_option(const Arguments *arguments, const char *name);

// Get value on index `idx` of option with name `name` from `arguments`, return NULL if not found
char *Arguments_get_option_value(const Arguments *arguments, const char*name, int idx);

// Check if `arguments` have option with name `name`
bool Arguments_has_option(const Arguments *arguments, const char *name);

// Check if `arguments` have `value`
bool Arguments_has_value(const Arguments *arguments, const char *name);

// Check if the subcommand of `arguments` is `subcommand`
bool Arguments_is_subcommand(const Arguments *arguments, const char *subcommand);

// Parse command line arguments and update to the `arguments`
void Arguments_parse(Arguments *arguments, int argc, char **argv);

// Free the `arguments` memory
void Arguments_free(Arguments *arguments);

