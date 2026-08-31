// Blob subcommand

#include <string.h>
#include <pthread.h>
#include <time.h>
#include "subs.h"
#include "sub_meta.h"
#include "utils.h"
#include "services/blob.h"
#include "characters.h"


// Register function
void sub_register_blob(void) {
    register_subcommand(
        (SubCommandMeta){
            .name = "blob",
            .short_description = "Download Blob",
            .long_description = "Download Blob or get info by hash.",
            .options_count = 3
        },
        (SubCommandOptionMeta[]){
            { .name="output", .alias="o", .value="filename", .type=ONE_VALUE },
            { .name="info", .alias="i", .type=ZERO_VALUE },
            { .name="no-download", .alias="D", .type=ZERO_VALUE },
        }
    );
}

// Helper functnions
static void print_blob_info(Blob *, bool);
static void *download_blob_thread_f(void *);

typedef struct {
    Blob *blob;
    char *filepath;
    Progress *progress;
} download_blob_thread_arg;


int sub_blob(const Arguments *args) {
    char *filepath = NULL;
    bool print_info, no_download, to_stdout = false;   

    printf_style(CH_BLACK_SQUARE " Blob\n");

    if (!args->value_count) {
        printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_RIGHT " ");
        printf_error("Proved hash for blob\n");
        return 0;
    }

    Blob *blob = Blob_get(args->values[0]);
    if (!blob) {
        printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_RIGHT " ");
        printf_error("No blob found with this hash\n");
        return 0;
    }

    if (Arguments_has_option(args, "output")) {
        filepath = Arguments_get_option_value(args, "output", 0);
    }
    if (!filepath) {
        filepath = args->values[args->value_count-1];
    }
    if (strcmp(filepath, "-") == 0) {
        filepath = "";
        to_stdout = true;
    }

    print_info = Arguments_has_option(args, "info");
    no_download = Arguments_has_option(args, "no-download");

    if (print_info) {
        print_blob_info(blob, !no_download);
    }

    if (!no_download) {
        pthread_t thread;
        void *thread_result;
        bool downloaded;
        Progress *progress = Progress_create("Downloading", blob->size);
        download_blob_thread_arg arg = { blob, filepath, progress };
        char *t;
        pthread_create(&thread, NULL, download_blob_thread_f, &arg );

        bool progress_completed = false;
        while (true && !to_stdout) { // don't show progress if it is to stdout
            progress_completed = Progress_is_completed(progress);
            t = Progress_to_string(progress, NULL);
            printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_RIGHT "%s\r", t);
            free(t);
            nanosleep(&(struct timespec){ 0, 200000000L }, NULL);
            if (progress_completed) {
                break;
            }
        }
        Progress_free(progress);
        if (!to_stdout) printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_RIGHT "\n");
        pthread_join(thread, &thread_result);
        downloaded = (bool)thread_result;

        if (!downloaded) {
            printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_RIGHT " ");
            printf_error("\033[31;1mBecause of some error, unable to download the blob.\033[m\n");
        } else if (!to_stdout) {
            printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_RIGHT " Blob downloaded.\n");
        }
    }

    Blob_free(blob);
    return 0;
}


static void print_blob_info(Blob *blob, bool would_download) {
    char *size = formate_size(blob->size);
    int i, j, size_len = strlen(size);;
    
    printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_RIGHT);
    for (i = 0; i < 18; i++) printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
    printf_style(CH_BOX_DRAWINGS_LIGHT_DOWN_AND_LEFT "\n");

    for (j = 0; j < 4; j++) {
        printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL " ");
        for (i = 0; i < 16; i++) {
            printf_output("%c", blob->hash[i+(j*16)]);
        }
        printf_style(" " CH_BOX_DRAWINGS_LIGHT_VERTICAL "\n");
    }

    printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_RIGHT);
    for (i = 0; i < 18; i++) printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
    printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_LEFT "\n");

    printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL " ");
    for (i = 0; i < 16 - size_len; i++) printf_style(" ");
    printf_output("%s", size);
    printf_style(" " CH_BOX_DRAWINGS_LIGHT_VERTICAL "\n");

    if (would_download) {
        printf_style(CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_RIGHT);
    } else {
        printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_RIGHT);
    }
    for (i = 0; i < 18; i++) printf_style(CH_BOX_DRAWINGS_LIGHT_HORIZONTAL);
    printf_style(CH_BOX_DRAWINGS_LIGHT_UP_AND_LEFT "\n");

    free(size);
}

static void *download_blob_thread_f(void *arg) {
    download_blob_thread_arg *dbta = arg;
    return (void*)Blob_download(dbta->blob, dbta->filepath, dbta->progress);
}

