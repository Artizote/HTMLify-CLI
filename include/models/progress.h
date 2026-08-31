// Progress

#pragma once

#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    char *title;
    size_t target;
    size_t current;
    bool started;
    bool finished;
    time_t start_time;
    time_t finish_time;
} Progress;


// Create new `Progress` struct
Progress *Progress_new(void);

// Intlize `progress` struct
void Progress_init(Progress *progress, const char *title, size_t target);

// Create and return new `Progress` sntruct with target
Progress *Progress_create(const char *title, size_t target);

// Increment n steps in `progress`
void Progress_update(Progress *progress, size_t n);

// Start the progress
void Progress_start(Progress *progress);

// Finish the progress
void Progress_finish(Progress *progress);

// Store the string representation of `progress` bar in `string` if provided
// else return malloced string
char *Progress_to_string(Progress *progress, char *string);

// Return Estimated Time of progress coplition, in seconds
int Progress_estimated_time(Progress *progress);

// Return time elapse sinse progress started
int Progress_elasped_time(Progress *progress);

// Return progress in percent
float Progress_to_percent(Progress *progress);

// Return if target of `progress` is completed
bool Progress_is_completed(Progress *progress);

// Return if `progress` is started
bool Progress_is_started(Progress *progress);

// Return if `progress` is finished
bool Progress_is_finished(Progress *progress);

// Free Progress struct
void Progress_free(Progress *progress);

