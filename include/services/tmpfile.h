// TmpFile

#include <stdio.h>
#include <stdbool.h>
#include "services/blob.h"
#include "models/progress.h"
#include "cJSON.h"


typedef struct {
    char *id;
    char *name;
    Blob *blob;
} TmpFile;

/*
{
  "id": "string",
  "name": "string",
  "url": "https://example.com/",          // ignoring because recunstrable
  "blob_hash": "string",
  "expiry": "2026-09-08T00:47:12.857Z"   // ignoring the expiry, because
}                                        // the format may change in future
*/


// Create a new `TmpFile` struct
TmpFile *TmpFile_new(void);

// Initlize the `tmpfile` with values
void TmpFile_init(TmpFile *tmpfile, const char *id, const char *name, const char *blab_hash);

// Initlize the `tmpfile` with values from `json`
void TmpFile_init_from_json(TmpFile *tmpfile, const cJSON *json);

// Get `TmpFile` by `id`
TmpFile *TmpFile_get(const char *id);

// Upload the contents from `file` and create a new `TmpFile`
TmpFile *TmpFile_create(FILE *file, const char *name, Progress *progress); 

// Upload the contens of file present on `filepath` and create new `TmpFile`
TmpFile *TmpFile_upload(const char *filepath, const char *name, Progress *progress);

// Write the contents of `tmpfile` into `file`
bool TmpFile_write(TmpFile *tmpfile, FILE *file, Progress *progress);

// Download the tmpfile on filepath 
bool TmpFile_download(TmpFile *tmpfile, char *filepath, Progress *progress);

// Free the `TmpFile` struct
void TmpFile_free(TmpFile *tmpfile);

