/*
 * Tree
 */
#ifndef __TREE__
#define __TREE__

#include <string.h>

#include "Stack.h"
#include "Queue.h"

typedef struct __Tree__ {
  size_t length;
  Node* root;

  /**
   * @private
   */
  Stack _searchStack;
} Tree;

Tree    tree(size_t size, ...);

void    tr_insert(Tree*, void*);
void    tr_erase(Tree*, void*);

void*   tr_at(Tree*, void*);
void    tr_clear(Tree* tree);

Node* tr_begin(Tree*);
Node* tr_next(Tree*);
Node* tr_end(Tree*);
Node* tr_prev(Tree*);
int      tr_done(void* iter);

/**
 * @private
 */
void __walk(Tree* tree, Node** iter, const char* direction) {
  while (1) {
    if (strcmp(direction, "next")) {
      if ((*iter)->prev != NULL) {
        *iter = (*iter)->prev;
        st_push(&tree->_searchStack, *iter);
      } else break;
    } else {
      if ((*iter)->next != NULL) {
        *iter = (*iter)->next;
        st_push(&tree->_searchStack, *iter);
      } else break;
    }
  }
}

/**
 * @private
 */
int __append(Node** target, Node** iter, void* element) {
  if (*target == NULL) {
    *target = create_node(element);
    return 1;
  } else {
    *iter = *target;
    return 0;
  }
}

/**
 * @private
 */
Node** __lowest(Node** target, const char* direction) {
  Node** lowest = strcmp(direction, "next") ? &(*target)->prev : &(*target)->next;
  while (1) {
    if (strcmp(direction, "next")) {
      if ((*lowest)->next != NULL) lowest = &(*lowest)->next;
      else break;
    } else {
      if ((*lowest)->prev != NULL) lowest = &(*lowest)->prev;
      else break;
    }
  }
  (*target)->element = (*lowest)->element;
  return lowest;
}

/**
 * @private
 */
void* __remove(Tree * tree, Node** target) {
  if ((*target)->next == NULL && (*target)->prev == NULL) {
    free(*target); *target = NULL;
    return (void*) 1;
  } else {
    if (tree->root != (*target)) {
      if (((*target)->next != NULL && (*target)->prev != NULL)) {
        return __lowest(target, "next");
      } else {
        Node* t = (*target)->next != NULL ? (*target)->next : (*target)->prev;
        free(*target); *target = t;
        return (void*) 1;
      }
    } else {
      if (((*target)->next != NULL)) {
        return __lowest(target, "next");
      } else {
        return __lowest(target, "prev");
      }
    }
  }
  return NULL;
}

/**
 * Create Binary Tree
 *
 * @public
 */
Tree tree(size_t size, ...) {
  Tree tr = { .length = 0, .root = NULL, ._searchStack = stack(0) };
  va_list ap;
  va_start(ap, size);
  for (int i = 0; i < size; i++) {
    tr_insert(&tr, va_arg(ap, void*));
  }
  va_end(ap);
  return tr;
}

/**
 * Insert new node
 *
 * @public
 */
void tr_insert(Tree* tree, void* element) {
  if (tree->root != NULL) {
    Node* iter = tree->root;
    while (1) {
      if (iter->element < element) {
        if (0 != __append(&iter->next, &iter, element)) break;
      } else {
        if (0 != __append(&iter->prev, &iter, element)) break;
      }
    }
  } else {
    tree->root = create_node(element);
  }
  tree->length++;
}

/**
 * Remove node with element
 *
 * @public
 */
void tr_erase(Tree* tree, void* element) {
  void* lowest = NULL;
  for (Node* iter = tr_begin(tree); 1 != tr_done(iter); iter = tr_next(tree, &iter)) {
    if (iter->next != NULL && iter->next->element == element) {
      if (NULL != (lowest = (Node**) __remove(tree, &iter->next))) break;
    } else if (iter->prev != NULL && iter->prev->element == element) {
      if (NULL != (lowest = (Node**) __remove(tree, &iter->prev))) break;
    } else if (iter->element == element && tree->root->element == element) {
      if (NULL != (lowest = (Node**) __remove(tree, &iter))) break;
    }
  }
  if (lowest != NULL && lowest != 1) {
    __remove(tree, (Node**) lowest);
  }
  tree->length--;
}

/**
 * Get node with element
 *
 * @public
 */
void* tr_at(Tree* tree, void* element) {
  Node* at = tree->root;
  Node* current = at;
  Queue searchQueue = queue(0);
  int done = 0;

  for (int i = 0; i < tree->length; i++) {
    if (current != NULL && current->element == element) return (Node*) current;
    if (searchQueue.length > 0 && done == 1) {
      at = (Node*)qu_front(&searchQueue);
      qu_pop(&searchQueue);
      done = 0;
    }
    if (at->prev != NULL && current != at->prev && done == 0) {
      current = at->prev;
      if (at->next == NULL) done = 1;
    } else if (at->next != NULL && current != at->next && done == 0) {
      current = at->next;
      done = 1;
    }
    if (current != NULL) {
      if (current->next != NULL || current->prev != NULL) {
        qu_push(&searchQueue, current);
      }
    }
  }
  return NULL;
}

/**
 * Clear binary tree
 * 
 * @public
 */
void tr_clear(Tree* tree) {
  Queue elements = queue(0);
  for (Node* iter = tr_begin(tree); 1 != tr_done(iter); iter = tr_next(tree, &iter)) {
    qu_push(&elements, iter->element);
  }
  size_t s = tree->length;
  for (int i = 0; i < s; i++) {
    tr_erase(tree, qu_front(&elements));
    qu_pop(&elements);
  }
  qu_clear(&elements);
}


/**
 * Get first node by in order
 *
 * @public
 */
Node* tr_begin(Tree* tree) {
  Node* iter = tree->root;
  st_clear(&tree->_searchStack);

  st_push(&tree->_searchStack, iter);
  __walk(tree, &iter, "prev");

  st_pop(&tree->_searchStack);
  return iter;
}

/**
 * Get next node by in order
 *
 * @public
 */
Node* tr_next(Tree* tree, Node** iter) {
  if ((*iter)->next != NULL) {
    *iter = (*iter)->next;
    st_push(&tree->_searchStack, *iter);
    __walk(tree, iter, "prev");
  }
  if (tree->_searchStack.top != NULL) {
    *iter = (Node*)st_top(&tree->_searchStack);
    st_pop(&tree->_searchStack);
    return *iter;
  }
  return NULL;
}

/**
 * Get last node by in order
 *
 * @public
 */
Node* tr_end(Tree* tree) {
  Node* iter = tree->root;
  st_clear(&tree->_searchStack);

  st_push(&tree->_searchStack, iter);
  __walk(tree, &iter, "next");

  st_pop(&tree->_searchStack);
  return iter;
}

/**
 * Get prev node by in order
 *
 * @public
 */
Node* tr_prev(Tree* tree, Node** iter) {
  if ((*iter)->prev != NULL) {
    *iter = (*iter)->prev;
    st_push(&tree->_searchStack, *iter);
    __walk(tree, iter, "next");
  }
  if (tree->_searchStack.top != NULL) {
    *iter = (Node*)st_top(&tree->_searchStack);
    st_pop(&tree->_searchStack);
    return *iter;
  }
  return NULL;
}

/**
 * is Done
 *
 * @public
 */
int tr_done(void* iter) {
  if (iter == NULL) {
    return 1;
  }
  return 0;
}

#endif // !__BINARY_TREE__
