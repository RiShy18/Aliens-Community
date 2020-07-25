#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <structs.h>

/* THIS FILE IS A WRAPPER OF LINKEDLIST.C
*/

//wrapper level functions
struct node_t* listGetHead(list *l) {
	return l->head;
}

//public functions from linkedlist.h
list* listInit() {
	list* l = (list* )malloc(sizeof(list));
	l->head = NULL;
	return l;
}
void listPrint(list *l) {
	printList(l->head);
}
bool listContains(list* l, void* data) {
	return containsNode(l->head, data);
}
void listInsertHead(list* l, void* data) {
	l->head = insertHead(l->head, data);
}
void listInsertTail(list* l, void* data) {
	l->head = insertTail(l->head, data);
}
void listDeleteNode(list* l, void* data) {
	l->head = deleteNode(l->head, data);
}
int listSize(list* l) {
	return sizeList(l->head);
}
void listFree(list* l) {
	freeList(l->head);
}

llist *llist_create(void *new_data)
{
  struct node *new_node;

  llist *new_list = (llist *)malloc(sizeof (llist));
  *new_list = (struct node *)malloc(sizeof (struct node));
  
  new_node = *new_list;
  new_node->data = new_data;
  new_node->next = NULL;
  return new_list;
}

void llist_free(llist *list)
{
  struct node *curr = *list;
  struct node *next;

  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }

  free(list);
}

void llist_push(llist *list, void *data)
{
  struct node *head;
  struct node *new_node;
  if (list == NULL || *list == NULL) {
      fprintf(stderr, "llist_add_inorder: list is null\n");
  }

  head = *list;
  
  // Head is empty node
  if (head->data == NULL){
      head->data = data;
  // Head is not empty, add new node to front
  } else {
      new_node = malloc(sizeof (struct node));
      new_node->data = data;
      new_node->next = head;

      *list = new_node;
  }
}

void llist_insert_end(llist *list, void* data){
  struct node *head;
  struct node *new_node;

  head = *list;

  if (head->data == NULL){
    head->data = data;
  } else {
    while(head->next != NULL) {
      head = head->next;
    }
    new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    head->next = new_node;
  }
}

void* llist_pop(llist *list)
{
  void *popped_data;
  struct node *head = *list;

  if (list == NULL || head->data == NULL)
      return NULL;

  popped_data = head->data;
  
  if(llist_get_size(list) == 1) {
    head->data = NULL;
  } else {
    *list = head->next;
    free(head);
  }

  return popped_data;
}

int llist_get_size(llist* list) {
  struct node* head = *list;

  if(head->data == NULL || head == NULL) {
    return 0;
  }

  int counter = 1;

  while(head->next != NULL) {
    head = head->next;
    counter += 1;
  }
  return counter;
}

void llist_insert_scheduler_attribute(llist *list, void *data, int comparation){
  /**
  *
  * comparation == 0 // Prioridad
  * comparation == 1 // Duracion
  *
  */
  struct node *head;
  struct node *new_node;
  float atributo = *((float*) data + comparation);
  int index = 0;

  head = *list;

  if (head->data == NULL){
    head->data = data;
  } else {
    while(*((float*)head->data + comparation) <= atributo) {
      index++;
      if(head->next == NULL) break;
      head = head->next;
    }
    llist_insert_by_index(list, data, index);
  }
}

void* llist_get_by_index(llist *list, int index) {
  void *popped_data;
  struct node *curr = *list;
  int list_size = llist_get_size(list);

  if(list_size <= index) {
    printf("Index out of range\n");
    return NULL;
  }

  for(int i = 0; i < index; i++){
    curr = curr->next;
  }

  popped_data = curr->data;

  return popped_data;
}

int llist_remove_by_index(llist *list, int Id)
{
  struct node *curr = *list;
  struct node *temp = *list;
  if (list == NULL || *list == NULL) {
    return 1;
  }

  if (llist_get_size(list)-1 < Id){
    return 1;
  }

  if (Id == 0){
    if(llist_get_size(list) == 1) {
      curr->data = NULL; 
    } else {
      *list = curr->next;
    }
    return 0;
  }
  
  for(int i = 0; i < Id-1; i++){
    if (list == NULL || curr->next == NULL)
      return 1;
    curr = curr->next;
    temp = temp->next;
  }

  temp = temp->next;
  curr->next = temp->next;

  free(temp);
  return 0;
}

void llist_print(llist *list)
{
  struct node *curr = *list;
  alien *thisAlien;
  while (curr != NULL) {
    thisAlien = (alien *)curr->data;
    printf("Alien: Duracion - %f, Prioridad - %f\n\n", thisAlien->duration, thisAlien->priority);
    curr = curr->next;
  }
}

int llist_insert_by_index(llist *list,void *data, int Id)
{
  struct node *curr = *list;
  struct node *new_node;
  if (list == NULL || *list == NULL) {
    return 1;
  }

  if (llist_get_size(list)-1 < Id) {
    llist_insert_end(list,data);
  } else if(Id == 0) {
    llist_push(list,data);
  } else {
    for(int i = 0; i < Id-1; i++){
      if (list == NULL || curr->next == NULL)
        return 1;
      curr = curr->next;
    }
    new_node = malloc(sizeof (struct node));
    new_node->data = data;
    new_node->next = curr->next;
    curr->next = new_node;
  }
  return 0;
}

void* llist_get_winner(llist *list, int winner) {
  alien* new_alien;
  void *popped_data;
  struct node *curr = *list;
  int list_size = llist_get_size(list);

  printf("Largo de lista %d\n", list_size);

  if(list_size < 1) {
    printf("Lista vacia\n");
    return NULL;
  }

  printf("List size get winner: %d\n", list_size);

  for(int i = 0; i < list_size ; i++){
    new_alien = (alien*) curr->data;
    if ((*new_alien->lottery_numbers == winner || *(new_alien->lottery_numbers + 1) == winner)  && (new_alien->working != 1)){
      printf("Ganador el tiquete %d con el alien con duracion %f!\n", winner, new_alien->duration);
      return curr->data;
    }
    curr = curr->next;
  }

  return NULL;
}

int llist_get_alien_index(llist *list, int id)
{
  struct node *curr = *list;
  alien *thisAlien;

  int counter = 0;
  while (curr != NULL)
  {
    thisAlien = (alien *)curr->data;

    if (thisAlien->id == id)
    {
      return counter;
    }

    counter++;
    curr = curr->next;
  }

  return -1;
}