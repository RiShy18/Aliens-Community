/* llist.h
 * Generic Linked List
 * https://gist.github.com/meylingtaing/11018042
 */

struct node {
    void *data;
    struct node *next;
};

typedef struct node * llist;

/* create: Create a linked list */
llist *create(void *data);

/* free: Free a linked list */
void lfree(llist *list);

/* add_inorder: Add to sorted linked list */
int add_inorder(void *data, llist *list, 
                       int (*comp)(void *, void *));

/* push: Add to head of list */
void push(llist *list, void *data);

/* pop: remove and return head of linked list */
void *pop(llist *list);

/* print: print linked list */
void print(llist *list, void (*print)(void *data));

/* getbyId: get item of linked list by Id */
void *getbyId(llist *list, int Id);

/* addLast: add item to tale of linked list */
void addLast(llist *list, void *data);

/* delById: delete item of linked list serched by Id */
int delById(llist *list, int Id);

/* getSize: get size of linked list */
int getSize(llist *list);

/* addById: add item to linked list in a specific pos */
int addById(llist *list,void *data, int Id);