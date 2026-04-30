// SubCommand Metas

#pragma once

typedef enum {
    ZERO_VALUE,
    ONE_VALUE,
    ZERO_OR_ONE_VALUE,
    ONE_OR_MORE_VALUE,
    ZERO_OR_MORE_VALUE,
} SubCommandOptionType;

typedef struct {
    char *name;
    char *alias;
    char *value;
    SubCommandOptionType type;
} SubCommandOptionMeta;

typedef struct {
    char *name;
    char *short_description;
    char *long_description;
    int options_count;
    SubCommandOptionMeta *options;
} SubCommandMeta;

// return Meta for subcommand
SubCommandMeta *get_subcommand_meta(const char *subcommand);

// return Meta for option of subcommand
SubCommandOptionMeta *get_subcommand_option_meta(const char *subcommand, const char *option);

// register subcommand meta
void register_subcommand(SubCommandMeta meta, SubCommandOptionMeta options_meta[]);

// Register all subcommands
void register_subcommands(void);

