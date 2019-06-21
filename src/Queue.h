/*
 * Queue
 */
#ifndef __QUEUE__
#define __QUEUE__

#include "Node.h"

typedef struct __Queue__ {
  size_t length;

  Node* front;
  Node* rear;
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
  Queue qu = { .length = 0, .front = NULL, .rear = NULL };
  va_list ap;
  va_start(ap, size);
  for (int i = 0; i < size; i++) {
    qu_push(&qu, va_arg(ap, void*));
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
  Node* node = create_node(element);
  if (queue->rear != NULL) {
    node->prev = queue->rear;
    node->next = NULL;
    queue->rear->next = node;
  } else if (queue->front == NULL && queue->rear == NULL) {
    queue->front = node;
  }
  queue->rear = node;
  queue->length++;
}

/**
 * Remove node at Front
 *
 * @public
 */
void qu_pop(Queue* queue) {
  Node* node = queue->front;
  if (queue->front->next != NULL) {
    queue->front = queue->front->next;
    queue->front->prev = NULL;
  } else {
    queue->rear = NULL; queue->front = NULL;
  }
  free(node);
  queue->length--;
}

/**
 * Clear Queue
 *
 * @public
 */
void qu_clear(Queue* queue) {
  size_t s = queue->length;
  for (size_t i = 0; i < s; i++) {
    qu_pop(queue);
  }
}

/**
 * Get front element
 *
 * @public
 */
void* qu_front(Queue* queue) {
  if (queue->front != NULL) {
    return queue->front->element;
  }
}

/**
 * Get rear element
 *
 * @public
 */
void* qu_rear(Queue* queue) {
  if (queue->rear != NULL) {
    return queue->rear->element;
  }
}

#endif // !__QUEUE__

