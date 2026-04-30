// Sub commands

#pragma once


#include "argparse.h"

// Help subcommand
// show help text
int sub_help(const Arguments *args);

// Version subcommand
// show the utility version
int sub_version(const Arguments *args);

// ShortLink subcommand
// Create, and retrive shortlinks
int sub_shortlink(const Arguments *args);


// SubCommand meta register functions
void
sub_register_help(void),
sub_register_version(void),
sub_register_shortlink(void)
;

