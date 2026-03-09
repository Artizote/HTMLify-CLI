// ShortLink service

# pragma once

#include <stdbool.h>
#include "cJSON.h"


typedef struct ShortLink {
    int id;
    char *href;
    char *_short;
    int hits;
    char *url;
} ShortLink;

/*
{
  "id": 0,
  "href": "string",
  "short": "string",
  "hits": 0,
  "url": "string"
}
*/

// Create new ShortLink struct
ShortLink *ShortLink_new(void);

// Initiate the `shortlink`
void Shortlink_init(ShortLink *shortlink, int id, char *href, char *_short, int hits, char *url);

// Initiate the `shortlink` with values from `json`
void ShortLink_init_from_json(ShortLink *shortlink, const cJSON *json);

// Create short link return `ShortLink`
ShortLink *ShortLink_create(char *url, bool new);

// Crate `ShortLink` with values from `json`
ShortLink *ShortLink_create_from_json(const cJSON *json);

// Find and return `Shortlink` by `id`
ShortLink *ShortLink_get_by_id(int id);

// Find and return `ShortLink` by `_short`
ShortLink *ShortLink_get_by_short(const char *_short);

// Free the `shortlink` from memory
void ShortLink_free(ShortLink *shortlink);

