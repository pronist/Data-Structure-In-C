/*
 * Stack
 */
#ifndef __STACK__
#define __STACK__

#include "Node.h"

typedef struct __Stack__ {
  size_t length;

  Node* top;
  Node* bottom;
} Stack;

Stack stack(size_t size, ...);

void  st_push(Stack*, void*);
void  st_pop(Stack*);

void  st_clear(Stack*);

void* st_top(Stack*);

/**
 * Create Stack
 *
 * @public
 */
Stack stack(size_t size, ...) {
  Stack st = { .length = 0, .top = NULL, .bottom = NULL };
  va_list ap;
  va_start(ap, size);
  for (int i = 0; i < size; i++) {
    st_push(&st, va_arg(ap, void*));
  }
  va_end(ap);
  return st;
}

/**
 * Push new node at Back
 *
 * @public
 */
void st_push(Stack* stack, void* element) {
  Node* node = create_node(element);
  if (stack->top != NULL) {
    node->prev = stack->top;
    node->next = NULL;
    stack->top->next = node;
  } else if (stack->bottom == NULL && stack->top == NULL) {
    stack->bottom = node;
  }
  stack->top = node;
  stack->length++;
}

/**
 * Remove node at Back
 *
 * @public
 */
void st_pop(Stack* stack) {
  Node* node = stack->top;
  if (stack->top->prev != NULL) {
    stack->top = stack->top->prev;
    stack->top->next = NULL;
  } else {
    stack->top = NULL; stack->bottom = NULL;
  }
  free(node);
  stack->length--;
}

/**
 * Clear Stack
 *
 * @public
 */
void st_clear(Stack* stack) {
  size_t s = stack->length;
  for (size_t i = 0; i < s; i++) {
    st_pop(stack);
  }
}

/**
 * Get top element
 *
 * @public
 */
void* st_top(Stack* stack) {
  if (stack->top != NULL) {
    return stack->top->element;
  }
  return NULL;
}

#endif // !__STACK__
