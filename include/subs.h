// Sub commands

#pragma once


#include "argparse.h"

// Main subcommand
// just the main command
int sub_main(const Arguments *args);

// Help subcommand
// show help text
int sub_help(const Arguments *args);

// Version subcommand
// show the utility version
int sub_version(const Arguments *args);

// ShortLink subcommand
// Create, and retrive shortlinks
int sub_shortlink(const Arguments *args);

// Print Config subcommand
// Pirnts the confgi variables
int sub_print_config(const Arguments *args);


// SubCommand meta register functions
void
sub_register_main(void),
sub_register_help(void),
sub_register_version(void),
sub_register_shortlink(void),
sub_register_print_config(void)
;

