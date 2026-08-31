// Blob

#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "models/progress.h"
#include "cJSON.h"


typedef struct {
    char hash[66];
    size_t size;
} Blob;

/*
{
  "hash": "string",
  "size": 0
}
*/

// Create new `Blob` struct
Blob *Blob_new(void);

// Intlize `blob` with values
void Blob_init(Blob *blob, const char *hash, size_t size);

// Intlize `blob` from json
void Blob_init_from_json(Blob *blob, cJSON *json);

// Return initlized `Blob` struct if blob found with provided hash
Blob *Blob_get(const char *hash);

// Write blob to given file descriptor, returns number of bytes written
bool Blob_write(Blob *blob, FILE *file, Progress *progress);

// Download `blob` to given `filepath`, return success status
bool Blob_download(Blob *blob, const char *filepath, Progress *progress);

// Free the blob memory
void Blob_free(Blob *blob);

