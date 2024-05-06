#include "list.h"


typedef struct lnode *link;
struct lnode{void* data; link next;};

struct list{link head, tail; unsigned int length;};

struct list_iterator{List_t lu; link current;};

link lnode_new(void *data){
	link newnode=(link) malloc(sizeof(*newnode));
	if (newnode == NULL) return NULL;
	newnode->data=data;
	newnode->next=NULL;
	return newnode;
}

List_t List_new(void){
	List_t l=(List_t) malloc(sizeof(*l));
	if(l==NULL)return NULL;
	l->head=l->tail=NULL;
	l->length=0;
return l;
}

int List_add(List_t l, void *data){
	if(l==NULL) return 0;
	if(l->head==NULL){
		l->tail=lnode_new (data);
		l->head=l->tail;
	}else{
	l->tail->next=lnode_new(data);
		if(l->tail->next==NULL)return 0;
	l->tail=l->tail->next;
	}
return ++(l->length);
}

int List_length(List_t l){
if(l==NULL) return 0;
return l->length;
}

void* List_search(List_t l, void *key, int (*cmp)(const void *e1, const void *e2)){
link nd;
if(l==NULL)return NULL;
nd=l->head;
	while(nd != NULL){
		if((cmp(key,nd->data))==0) return nd->data;
		nd=nd->next;
	}
return NULL;
}

void List_free(List_t l){
link nd=l->head;
	while(nd != NULL){
		link t = nd;
		nd=nd->next;
		free(t);
	}
free(l);
}

LIter_t List_iterator(List_t l){
if(l==NULL) return NULL;
LIter_t it = (LIter_t) malloc (sizeof(*it));
if(it==NULL) return NULL;
it->lu=l;
it->current=l->head;
return it;
}

int LIterator_hasNext(LIter_t it){
if(it==NULL) return 0;
return it->current != NULL;
}

void* LIterator_next(LIter_t it){
if(it==NULL) return NULL;
if(!LIterator_hasNext(it)) return NULL;
link nd = it->current;
it->current=it->current->next;
return nd->data;
}

void LIterator_free(LIter_t it){
free(it);
}

void* List_delete(List_t l, void *key, int (*cmp)(const void *e1, const void *e2)){
link nd;
link prev;
void* data =NULL;
if(l==NULL)return NULL;
nd=l->head;
prev = NULL;
	while(nd != NULL){
		if((cmp(key,nd->data))==0){
			data=nd->data;
			if(nd==l->head){
				l->head = nd->next;	
			}else{
				prev->next=nd->next;
			}
			if(nd==l->){
				l->tail=prev;
			}
			free(nd);
			l->length--;
			break;
		}
		prev=nd;
		nd = nd->next;
	}
return data;
}
