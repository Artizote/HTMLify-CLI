// Queue data structure

#include <stdlib.h>
#include <stdbool.h>

/*
 * Dynamic Generic Queue
 *
 * Shrinks and Expands as per number
 * of items present in queue
 */
typedef struct {
    size_t cap;
    size_t used;
    void **items;
} Queue;


// Create new `Queue` struct
Queue *Queue_new(void);

// Initlize `queue` with cap
void Queue_init(Queue *queue, size_t cap);

// Return an initlized `Queue`, with capicity of 16
Queue *Queue_create(void);

// Add `item` to `queue`
void Queue_push(Queue *queue, void *item);

// Get first item from `queue` or NULL if `queue` is empty
void *Queue_get(Queue *queue);

// Determine if `queue` capicity should expand
bool Queue_should_expand(Queue *queue);

// Determine if `queue` capicity should shrink
bool Queue_should_shrink(Queue *queue);

// Expend the Queue capacity by ~1.5 factor
void Queue_expand(Queue *queue);

// Shrink the Queue capacity
void Queue_shrink(Queue *queue);

// Return number of items present in `queue`
int Queue_get_item_count(Queue *queue);

// Check if `queue` is empty
bool Queue_is_empty(Queue *queue);

// Check if `queue` is full
bool Queue_is_full(Queue *queue);

// Free the `Queue`
void Queue_free(Queue *queue);

