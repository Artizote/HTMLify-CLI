// ShortLink subcommand

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "subs.h"
#include "sub_meta.h"
#include "argparse.h"
#include "services/shortlink.h"
#include "characters.h"
#include "utils.h"


// Meta Register Function

void sub_register_shortlink(void) {
    register_subcommand(
        (SubCommandMeta){
            .name = "shortlink",
            .short_description = "Create/Get ShortLinks",
            .long_description = "Get ShortLinks with id or short, or create ShortLinks for URLs.",
            .options_count = 3
        }, (SubCommandOptionMeta[]){
            { .name="id", .value="id", .type=ONE_OR_MORE_VALUE },
            { .name="short", .value="short", .type=ONE_OR_MORE_VALUE },
            { .name="new", .alias="n", .type=ZERO_VALUE},
        }
    );
}


// helper functions

static inline void
    print_input_line_style(void),
    print_last_input_line_style(void),
    print_output_line_style(void),
    print_last_output_line_style(void)
;


// Private stuff

typedef struct query {
    char *value;
    char type; // u -> url, i -> id, s -> short
} query;

static int query_count = 0;
static query *queries;

static void add_query(char *value, char type);


int sub_shortlink(const Arguments *args) {
    int ret_code = 0;

    printf_style(CH_BLACK_SQUARE " ShortLink\n");

    if (!args->value_count && !args->option_count) {
        printf_style(CH_BOX_DRAWINGS_LIGHT_ARC_UP_AND_RIGHT CH_BLACK_RIGHT_POINTING_TRIANGLE " ");
        printf_error("Provide URL to create shortlink or lookup by id or short\n");
        ret_code = 0;
        return ret_code;
    }

    bool flag_new = Arguments_has_option(args, "new");

    int i;

    // accumlating queries
    for (i = 0; i < args->value_count; i++) {
        add_query(args->values[i], 'u');
    }
    if (Arguments_has_option(args, "url")) {
        Option *option = Arguments_get_option(args, "url");
        for (i = 0; i < option->value_count; i++) {
            add_query(option->values[i], 'u');
        }
    }
    if (Arguments_has_option(args, "id")) {
        Option *option = Arguments_get_option(args, "id");
        for (i = 0; i < option->value_count; i++) {
            add_query(option->values[i], 'i');
        }
    }
    if (Arguments_has_option(args, "short")) {
        Option *option = Arguments_get_option(args, "short");
        for (i = 0; i < option->value_count; i++) {
            add_query(option->values[i], 's');
        }
    }

    // processing queries
    for (i = 0; i < query_count; i++) {
        query query = queries[i];
        ShortLink *shortlink = NULL;
        switch (query.type) {
            case 'u':
                shortlink = ShortLink_create(query.value, flag_new);
                break;
            case 'i': {
                int id_to_lookup;
                sscanf(query.value, "%d", &id_to_lookup);
                shortlink = ShortLink_get_by_id(id_to_lookup);
                break;
            }
            case 's': {
                shortlink = ShortLink_get_by_short(query.value);
                break;
            }
        }

        // input line style
        if (!(i == query_count - 1)) {
            print_input_line_style();
        } else {
            print_last_input_line_style();
        }

        printf_style("%s\n", query.value);

        // output line style
        if (!(i == query_count - 1)) {
            print_output_line_style();
        } else {
            print_last_output_line_style();
        }

        if (!shortlink) {
            switch (query.type) {
                case 'u': printf_error("Unable to short this url."); break;
                case 'i': printf_error("No ShortLink found with this id."); break;
                case 's': printf_error("No ShortLink found with this short."); break;
            }
            printf_output("\n");
            ret_code = 1;
        } else {
            printf_output("%s\n", shortlink->url);
        }

        ShortLink_free(shortlink);
    }

    return ret_code;
}


static inline void print_input_line_style(void) {
    printf_style(
        CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_RIGHT
        CH_BOX_DRAWINGS_LIGHT_DOWN_AND_HORIZONTAL
        CH_BOX_DRAWINGS_LIGHT_HORIZONTAL
        " "
    );
}

static inline void print_last_input_line_style(void) {
    printf_style(
        CH_BOX_DRAWINGS_LIGHT_ARC_UP_AND_RIGHT
        CH_BOX_DRAWINGS_LIGHT_DOWN_AND_HORIZONTAL
        CH_BOX_DRAWINGS_LIGHT_HORIZONTAL
        " "
    );
}

static inline void print_output_line_style(void) {
    printf_style(
        CH_BOX_DRAWINGS_LIGHT_VERTICAL
        CH_BOX_DRAWINGS_LIGHT_ARC_UP_AND_RIGHT
        CH_BLACK_RIGHT_POINTING_TRIANGLE
        " "
    );
}

static inline void print_last_output_line_style(void) {
    printf_style(
        " "
        CH_BOX_DRAWINGS_LIGHT_ARC_UP_AND_RIGHT
        CH_BLACK_RIGHT_POINTING_TRIANGLE
        " "
    );
}


static void add_query(char *name, char type) {
    query_count++;
    queries = reallocarray(queries, query_count, sizeof(query));
    queries[query_count-1] = (query){name, type};
}

