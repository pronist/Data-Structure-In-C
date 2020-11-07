/*
 * Queue
 */
#ifndef __QUEUE__
#define __QUEUE__

#include "List.h"

typedef struct __Queue__ {
  /**
   * @private
   */
  List _ls
} Queue;

Queue queue(size_t size, ...);

void  qu_push(Queue*, void*);
void  qu_pop(Queue*);

void  qu_clear(Queue*);

void* qu_front(Queue*);
void* qu_rear(Queue*);

/**
 * Create Queue
 *
 * @public
 */
Queue queue(size_t size, ...) {
  List ls = list(0);
  Queue qu = { ._ls = ls };
  va_list ap;
  va_start(ap, size);
  for (int i = 0; i < size; i++) {
    ls_push_back(&qu._ls, va_arg(ap, void*));
  }
  va_end(ap);
  return qu;
}

/**
 * Push new node at Back
 *
 * @public
 */
void qu_push(Queue* queue, void* element) {
  ls_push_back(&queue->_ls, element);
}

/**
 * Remove node at Front
 *
 * @public
 */
void qu_pop(Queue* queue) {
  ls_pop_front(&queue->_ls);
}

/**
 * Clear Queue
 *
 * @public
 */
void qu_clear(Queue* queue) {
  ls_clear(&queue->_ls);
}

/**
 * Get front element
 *
 * @public
 */
void* qu_front(Queue* queue) {
  return ls_begin(&queue->_ls)->element;
}

/**
 * Get rear element
 *
 * @public
 */
void* qu_rear(Queue* queue) {
  return ls_end(&queue->_ls)->element;
}

#endif // !__QUEUE__

