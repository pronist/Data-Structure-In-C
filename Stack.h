/*
 * Stack
 */
#ifndef __STACK__
#define __STACK__

#include "List.h"

typedef struct __Stack__ {
  /**
   * @private
   */
  List _ls
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
  List ls = list(0);
  Stack st = { ._ls = ls };
  va_list ap;
  va_start(ap, size);
  for (int i = 0; i < size; i++) {
    ls_push_back(&st._ls, va_arg(ap, void*));
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
  ls_push_back(&stack->_ls, element);
}

/**
 * Remove node at Back
 *
 * @public
 */
void st_pop(Stack* stack) {
  ls_pop_back(&stack->_ls);
}

/**
 * Clear Stack
 *
 * @public
 */
void st_clear(Stack* stack) {
  ls_clear(&stack->_ls);
}

/**
 * Get top element
 *
 * @public
 */
void* st_top(Stack* stack) {
  return ls_end(&stack->_ls)->element;
}

#endif // !__STACK__
