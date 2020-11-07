# DS

**DS** is Data Structure libaray in **C**

* **Fixed array**
* **Deque**
* **Linked list**
* **Queue**
* **Stack**
* **Tree (Binary Tree)**

## Fixed Array

### Array array(size_t, ...)

Create Array

```c
Array arr = array(1, "Hello, world!");
```

### void* ar_at(Array*, int)

Get element with position

```c
void* ele = ar_at(&arr, 0);
```

### void ar_clear(Array*)

Clear Array

```c
void* ele = ar_clear(&arr);
```

### Array Iterators

* void* ar_begin(Array*)
* void* ar_next(Array*)
* void* ar_end(Array*)
* void* ar_prev(Array*)
* int ar_done(void*)

```c
Array arr = array(1, "Hello, world!");
for (void* iter = ar_begin(&arr); 1 != ar_done(iter); iter = ar_next(&arr)) {
  // Hello, world!
  printf("%s", (const char*) iter);
}

ar_clear(&arr);
```

## Deque

### Deque deque(size_t, ...)

Create Deque

```c
Deque dq = deque(1, "Hello, world");
```

### void dq_push_front(Deque*, void*)

Push new node at Front

```c
dq_push_front(&dq, "Example");
```

### void dq_pop_front(Deque*)

Remove node at Front

```c
dq_pop_front(&dq);
```

### void dq_push_back(Deque*, void*)

Push new node at Back

```c
dq_push_back(&dq, "Example");
```

### void dq_pop_back(Deque*)

Remove node at Back

```c
dq_pop_back(&dq);
```

### void dq_insert(Deque*, void*, int)

Push element at Position

```c
dq_insert(&dq, "Example", 1);
```

### void dq_erase(Deque*, int)

Remove element at Position

```c
dq_erase(&dq, 1);
```

### void* dq_at(Deque*, int)

Get element with position

```c
void* ele = dq_at(&dq, 1);
```

### void dq_clear(Deque*)

Clear Deque

```c
dq_clear(&dq);
```

### Deque Iterators

* void* dq_begin(Deque*)
* void* dq_next(Deque*)
* void* dq_end(Deque*)
* void* dq_prev(Deque*)
* int dq_done(void*)

```c
Deque dq = deque(1, "Hello, world!");
dq_push_back(&dq, "Example");

for (void* iter = dq_begin(&dq); 1 != dq_done(iter); iter = dq_next(&dq)) {
  // Hello, world!
  // Example
  printf("%s", (const char*) iter);
}

dq_clear(&dq);
```

## Linked list

### List list(size_t, ...)

Create Linked List

```c
List ls = list(1, "Hello, world!");
```

### void ls_push_front(List*, void*)

Push new node at Front

```c
ls_push_front(&ls, "Example");
```

### void ls_pop_front(List*)

Remove node at Front

```c
ls_pop_front(&ls);
```

### void ls_push_back(List*, void*)

Push new node at Back

```c
ls_push_back(&ls, "Example");
```

### void ls_pop_back(List*)

Remove node at Back

```c
ls_pop_back(&ls);
```

### void ls_insert(List*, Node*, void*)

Insert new node at **before** the node

```c
Node* n = ls_at(&ls, "Hello, world!");
ls_insert(&ls, n, "Hi!");
```

### void ls_erase(List*, Node*)

Remove node

```c
Node* n = ls_at(&ls, "Hello, world!");
ls_earse(&ls, n);
```

### Node* ls_at(List*, void*)

Get node with element

```c
Node* n = ls_at(&ls, "Hello, world!");
```

### void ls_clear(List*)

Clear Linked List

```c
ls_clear(&ls);
```

### Linked List Iterators

* Node* ls_begin(List*)
* Node* ls_next(Node*)
* Node* ls_end(List*)
* Node* ls_prev(Node*)
* int ls_done(Node*)

```c
List ls = list(1, "Hello, world!");
ls_push_front(&ls, "Example");

for (Node* iter = ls_begin(&ls); 1 != ls_done(iter); iter = ls_next(iter)) {
  // Example
  // Hello, world!
  printf("%s", (const char*) iter->element);
}

ls_clear(&ls);
```

## Queue

### Queue queue(size_t, ...)

Create Queue

```c
Queue qu = queue(1, "Hello, world!");
```

### void qu_push(Queue*, void*)

Push new node at Back

```c
qu_push(&qu, "Example");
```

### void qu_pop(Queue*)

Remove node at Front

```c
qu_push(&qu);
```

### void qu_clear(Queue*)

Clear Queue

```c
qu_clear(&qu);
```

### void* qu_front(Queue*)

Get front element

```c
void* ele = qu_front(&qu);
```

### void* qu_rear(Queue*)

Get rear element

```c
void* ele = qu_rear(&qu);
```

## Stack

### Stack stack(size_t, ...)

Create Stack

```c
Stack st = stack(1, "Hello, world!");
```

### void st_push(Stack*, void*)

Push new node at Back

```c
st_push(&st, "Example");
```

### void st_pop(Stack*)

Remove node at Back

```c
st_pop(&st);
```

### void st_clear(Stack*)

Clear Stack

```c
st_clear(&st);
```

### void* st_top(Stack*)

Get top element

```c
void* ele = st_top(&st);
```

## Tree

### Tree tree(size_t, ...)

Create Binary Tree

```c
Tree tr = tree(1, "Hello, "World"!);
```

### void tr_insert(Tree*, void*)

Insert new node

```c
tr_insert(&tr, "Example");
```

### void tr_erase(Tree*, void*)

Remove node with element

```c
tr_erase(&tr, "Example");
```

### Node* tr_at(Tree*, void*)

Get node with element

```c
Node* n = tr_at(&tr, "Example");
```

### void tr_clear(Tree*)

```c
tr_clear(&tr);
```

### Tree Iterators

* Node* tr_begin(Tree*)
* Node* tr_next(Tree*, Node**)
* Node* tr_end(Tree*)
* Node* tr_prev(Tree*, Node**)
* int tr_done(void*)

```c
Tree tr = tree(1, "Hello, world!");
tr_insert(&tr, "Example");

for (Node* iter = tr_begin(&tr); 1 != tr_done(iter); iter = tr_next(&tr, &iter)) {
  // Hello, world
  // Example
  printf("%s", (const char*) iter);
}

tr_clear(&tr);
```

## License

[MIT](https://github.com/pronist/Data-Structure-In-C/blob/master/LICENSE)

Copyright 2019-2020. [SangWoo Jeong](https://github.com/pronist). All rights reserved.
