// Sub-Command Meta

#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include "sub_meta.h"
#include "subs.h"


static SubCommandMeta *SUB_COMMAND_METAS[16];
static unsigned char SUB_COMMAND_META_COUNT = 0;
static void(*sub_command_register_funcs[16])(void) = {
    sub_register_main,
    sub_register_help,
    sub_register_version,
    sub_register_shortlink,
    sub_register_print_config,
};


SubCommandMeta *get_subcommand_meta(const char *name) {
    if (!name) {
        return NULL;
    }
    for (int i=0; i<SUB_COMMAND_META_COUNT; i++) {
        if (strcmp(SUB_COMMAND_METAS[i]->name, name) == 0) {
            return SUB_COMMAND_METAS[i];
        }
    }
    return NULL;
}

char **get_subcommand_names(void) {
    char **names = malloc(sizeof(char*)*SUB_COMMAND_META_COUNT);
    for (int i=0; i<SUB_COMMAND_META_COUNT; i++) {
        names[i] = strdup(SUB_COMMAND_METAS[i]->name);
    }
    return names;
}

int get_subcommand_count(void) {
    return SUB_COMMAND_META_COUNT;
}

SubCommandOptionMeta *get_subcommand_option_meta(const char *subcommand, const char *option) {
    SubCommandMeta *meta = get_subcommand_meta(subcommand);
    if (!meta) {
        return NULL;
    }
    for (int i=0; i<meta->options_count; i++) {
        if (strcmp(meta->options[i].name, option) == 0) {
            return &meta->options[i];
        }
        if (strcmp(meta->options[i].alias, option) == 0) {
            return &meta->options[i];
        }
    }
    return NULL;
}

void register_subcommand(SubCommandMeta meta, SubCommandOptionMeta options_meta[]) {
    SubCommandMeta *scmeta = malloc(sizeof(SubCommandMeta));
    scmeta->name = meta.name ? strdup(meta.name) : strdup("");
    scmeta->short_description = meta.short_description ? strdup(meta.short_description) : NULL;
    scmeta->long_description = meta.long_description ? strdup(meta.long_description) : NULL;
    scmeta->options_count = meta.options_count;

    scmeta->options = malloc(sizeof(SubCommandOptionMeta) * scmeta->options_count);
    for (int i=0; i<scmeta->options_count; i++) {
        scmeta->options[i].name = options_meta[i].name ? strdup(options_meta[i].name) : strdup("");
        scmeta->options[i].alias = options_meta[i].alias ? strdup(options_meta[i].alias) : strdup("");
        scmeta->options[i].value = options_meta[i].value ? strdup(options_meta[i].value) : strdup("");
        scmeta->options[i].type = options_meta[i].type;
    }

    SUB_COMMAND_METAS[SUB_COMMAND_META_COUNT++] = scmeta;
}

void register_subcommands(void) {
    for (unsigned int i=0; i<sizeof(sub_command_register_funcs)/sizeof(sub_command_register_funcs[0]); i++) {
        if (sub_command_register_funcs[i] != NULL) {
            sub_command_register_funcs[i]();
        }
    }
}

