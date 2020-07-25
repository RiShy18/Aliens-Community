/* llist.h
 * Generic Linked List
 */
#ifndef _LIST_H
#define _LIST_H
//wrapper for linked list. make it easier to use
#include "linkedlist.h"
typedef struct list_t {
	struct node_t* head;
} list;

//wrapper level functions
struct node_t* listGetHead(list *l);

//public functions from linkedlist.h
list* listInit();
void listPrint(list *l);
bool listContains(list* l, void* data);
void listInsertHead(list* l, void* data);
void listInsertTail(list* l, void* data);
void listDeleteNode(list* l, void* data);
int listSize(list* l);
void listFree(list* l);


struct node {
    void *data;
    struct node *next;
};

typedef struct node * llist;

/* llist_create: Create a linked list */
llist *llist_create(void *data);

/* llist_free: Free a linked list */
void llist_free(llist *list);

/* llist_push: Add to head of list */
void llist_push(llist *list, void *data);

/* llist_pop: remove and return head of linked list */
void* llist_pop(llist *list);

/* llist_print: print linked list */
void llist_print(llist *list);

void llist_insert_end(llist *list, void* data);

int llist_insert_by_index(llist *list,void *data, int Id);

void llist_insert_scheduler_attribute(llist *list, void *data, int comparation);

void* llist_get_by_index(llist *list, int index);

int llist_get_size(llist* list);

int llist_remove_by_index(llist *list, int Id);

void* llist_get_winner(llist *list, int winner);

int llist_get_alien_index(llist *list, int id);

#endif