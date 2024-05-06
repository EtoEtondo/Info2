#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct list *List_t;

typedef struct list_iterator *LIter_t;

List_t List_new(void);

int List_add(List_t l, void *data);

int List_length(List_t l);

void* List_search(List_t l, void *key, int (*cmp)(const void *e1, const void *e2)); 

void List_free(List_t l);

LIter_t List_iterator(List_t l);

int LIterator_hasNext(LIter_t it);

void* LIterator_next(LIter_t it);

void LIterator_free(LIter_t it);

void* List_delete(List_t l, void *key, int (*cmp)(const void *e1, const void *e2));

#endif
