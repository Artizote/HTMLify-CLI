// Progress

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "models/progress.h"
#include "characters.h"
#include "models/color.h"


Progress *Progress_new(void) {
    Progress *progress = malloc(sizeof(Progress));
    progress->title = malloc(64);
    return progress;
}

void Progress_init(Progress *progress, const char *title, size_t target) {
    strncpy(progress->title, title, 64-1);
    progress->target = target;
    progress->current = 0;
    progress->started = false;
    progress->finished = false;
    progress->start_time = 0;
}

Progress *Progress_create(const char *title, size_t target) {
    Progress *progress = Progress_new();
    Progress_init(progress, title, target);
    return progress;
}

void Progress_update(Progress *progress, size_t n) {
    if (!Progress_is_started(progress)) {
        Progress_start(progress);
    }
    progress->current += n;
}

void Progress_start(Progress *progress) {
    progress->started = true;
    time(&progress->start_time);
}

void Progress_finish(Progress *progress) {
    progress->finished = true;
    time(&progress->finish_time);
}

char *Progress_to_string(Progress *progress, char *string) {
    char *temps, *tempu, *ps = malloc(1024);
    int o = 0; // offset
    int pbw = 20; // Progress Bar Width
    int ppc = 100 / pbw; // percent per cell
    int i, j, poc;
    float percent = Progress_to_percent(progress);
    int elasped_time = Progress_elasped_time(progress);
    int estimated_time = Progress_estimated_time(progress);
    char spinner_chars[8][4] = {
        CH_BRAILLE_PATTERN_DOTS_1237,
        CH_BRAILLE_PATTERN_DOTS_1234,
        CH_BRAILLE_PATTERN_DOTS_1245,
        CH_BRAILLE_PATTERN_DOTS_1456,
        CH_BRAILLE_PATTERN_DOTS_4568,
        CH_BRAILLE_PATTERN_DOTS_5678,
        CH_BRAILLE_PATTERN_DOTS_3678,
        CH_BRAILLE_PATTERN_DOTS_2378,
    };
    char bar_chars[6][4] = {
        CH_SPACE,
        CH_LEFT_ONE_EIGHTH_BLOCK,
        CH_LEFT_ONE_QUARTER_BLOCK,
        CH_LEFT_HALF_BLOCK,
        CH_LEFT_THREE_QUARTERS_BLOCK,
        CH_FULL_BLOCK,
    };
    Color color_green =         {0x50, 0xcc, 0x50};
    Color color_green_light =   {0x70, 0xe0, 0x00};
    Color color_gray =          {0x80, 0x80, 0x80};


    // Spinner
    temps = Color_to_fg_color_escape_sequence(&color_green_light);
    o += sprintf(&ps[o], " %s%s\033[0m ", temps, spinner_chars[time(NULL)%8]);
    free(temps);

    // Title
    o += sprintf(&ps[o], "%s", progress->title);

    o += sprintf(&ps[o], " ⦉");

    // Progress bar
    for (i = 0; i < pbw; i++) {
        poc = 0;
        for (j = 0; j < ppc; j++) {
            if (((i * ppc) + j) < percent) {
                poc++;
            }
        }

        tempu = bar_chars[poc];
        temps = Color_to_fg_color_escape_sequence(&color_green);
        o += sprintf(&ps[o], "%s%s\033[0m", temps, tempu);
        free(temps);
    }

    o += sprintf(&ps[o], "⦊ ");

    // Percent
    o += sprintf(&ps[o], "%*.2f %%", 6, percent);

    o += sprintf(&ps[o], " " CH_BOX_DRAWINGS_LIGHT_VERTICAL " ");
    
    // Elasped and Estimeted time
    temps = Color_to_fg_color_escape_sequence(&color_gray);
    o += sprintf(
        &ps[o], "%02d%s:%s%02d - ETA %02d%s:%s%02d",
        elasped_time / 60,   (time(NULL)%2) ? temps : "", "\033[0m", elasped_time % 60,
        estimated_time / 60, (time(NULL)%2) ? temps : "", "\033[0m", estimated_time % 60
    );
    free(temps);


    if (string == NULL) {
        return ps;
    }

    free(string);
    string = strdup(ps);

    free(ps);
    return NULL;
}

int Progress_estimated_time(Progress *progress) {
    if (!progress->target) {
        return 0;
    }
    if (!progress->started) {
        return 0;
    }
    if (progress->finished) {
        return 0;
    }
    if (!progress->start_time) {
        return 0;
    }
    if (!Progress_elasped_time(progress)) {
        return 0;
    }
    float done_p = Progress_to_percent(progress);
    float left_p = 100.0 - done_p;
    float seconds_per_percent = Progress_elasped_time(progress) / done_p;
    float estimated_time = left_p * seconds_per_percent;
    return estimated_time;
}

int Progress_elasped_time(Progress *progress) {
    if (!progress->start_time) {
        return 0;
    }
    return time(NULL) - progress->start_time;
}

float Progress_to_percent(Progress *progress) {
    if (progress->current == 0) {
        return 0;
    }
    if (Progress_is_completed(progress)) {
        return 100;
    }
    return ((float)progress->current / (float)progress->target) * 100;
}

bool Progress_is_completed(Progress *progress) {
    if (progress->target == 0) {
        return false;
    }
    return progress->current >= progress->target;
}

bool Progress_is_started(Progress *progress) {
    return progress->started;
}

bool Progress_is_finished(Progress *progress) {
    return progress->finished;
}

void Progress_free(Progress *progress) {
    free(progress->title);
    free(progress);
}

