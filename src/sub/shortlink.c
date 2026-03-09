// ShortLink subcommand

#include <stdio.h>
#include <stdbool.h>
#include "subs.h"
#include "argparse.h"
#include "services/shortlink.h"

int sub_shortlink(const Arguments *args) {
    int ret_code = 0;

    if (!args->option_count) {
        fprintf(stderr, "Provide URL to create shortlink or lookup by id or short\n");
        ret_code = 0;
        return ret_code;
    }

    bool flag_new = Arguments_has_option(args, "n");

    if (Arguments_has_option(args, "")) { // sort the url(s)
        Option *urls = Arguments_get_option(args, "");
        for (int i = 0; i < urls->value_count; i++) {
            char *url_to_short = urls->values[i];
            ShortLink *shortlink = ShortLink_create(url_to_short, flag_new);
            if (!shortlink) {
                fprintf(stderr, "Unable to short this url\n");
                ret_code = 1;
            } else {
                printf("%s\n", shortlink->url);
            }
            ShortLink_free(shortlink);
        }
        return ret_code;
    }

    if (Arguments_has_option(args, "id")) {
        Option *ids = Arguments_get_option(args, "id");
        if (!ids->value_count) {
            fprintf(stderr, "provide id(s) to lookup\n");
            return ret_code;
        }
        for (int i = 0; i < ids->value_count; i++) {
            int id_to_lookup;
            sscanf(ids->values[i], "%d", &id_to_lookup);
            ShortLink *shortlink = ShortLink_get_by_id(id_to_lookup);
            if (!shortlink) {
                fprintf(stderr, "ShortLink not found with this id\n");
            } else {
                printf("%s\n", shortlink->url);
            }
            ShortLink_free(shortlink);
        }
        return ret_code;
    }

    if (Arguments_has_option(args, "short")) {
        Option *shorts = Arguments_get_option(args, "short");
        if (!shorts->value_count) {
            fprintf(stderr, "provide short(s) to lookup\n");
            return ret_code;
        }
        for (int i = 0; i < shorts->value_count; i++) {
            char *_short = shorts->values[i];
            ShortLink *shortlink = ShortLink_get_by_short(_short);
            if (!shortlink) {
                fprintf(stderr, "ShortLink not found with this short\n");
            } else {
                printf("%s\n", shortlink->url);
            }
            ShortLink_free(shortlink);
        }
        return ret_code;
    }

    return ret_code;
}
