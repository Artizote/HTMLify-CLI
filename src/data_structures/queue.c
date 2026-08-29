// Queue data strructure

#include "data_structures/queue.h"


Queue *Queue_new(void) {
    Queue *queue = malloc(sizeof(Queue));
    return queue;
}

void Queue_init(Queue *queue, size_t cap) {
    queue->cap = cap;
    queue->used = 0;
    queue->items = malloc(cap * sizeof(void*));
}

Queue *Queue_create(void) {
    Queue *queue = Queue_new();
    Queue_init(queue, 16);
    return queue;
}

void Queue_push(Queue *queue, void *item) {
    if (Queue_should_expand(queue)) {
        Queue_expand(queue);
    }
    queue->items[queue->used++] = item;
}

void *Queue_get(Queue *queue) {
    if (Queue_is_empty(queue)) {
        return NULL;
    }
    if (Queue_should_shrink(queue)) {
        Queue_shrink(queue);
    }
    void *item = queue->items[0];
    for (size_t i = 0; i < queue->used-1; i++) {
        queue->items[i] = queue->items[i+1]; 
    }
    queue->used--;
    return item;
}

bool Queue_should_expand(Queue *queue) {
    return queue->used >= queue->cap * 0.95;
}

bool Queue_should_shrink(Queue *queue) {
    return queue->used <= queue->cap * 0.30;
}

void Queue_expand(Queue *queue) {
    size_t new_cap = queue->cap * 1.5 + 1;
    queue->items = realloc(queue->items, new_cap * sizeof(void *));
    queue->cap = new_cap;
}

void Queue_shrink(Queue *queue) {
    size_t new_cap = queue->cap * 0.5 + 1;
    queue->items = realloc(queue->items, new_cap * sizeof(void *));
    queue->cap = new_cap;
}

int Queue_get_item_count(Queue *queue) {
    return queue->used;
}

bool Queue_is_empty(Queue *queue) {
    return queue->used == 0;
}

bool Queue_is_full(Queue *queue) {
    return queue->cap == queue->used;
}

void Queue_free(Queue *queue) {
    free(queue->items);
    free(queue);
}

