#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct listElement_struct {
  void *                      data;
  struct listElement_struct * next;
} listElement_t;

typedef struct {
  listElement_t * first;
  int             size;
  
  int             memoryAutoManaged;
  void (*printElement)(void *);
} linkedList_t;

linkedList_t * make_linkedList ();
void           free_linkedList(linkedList_t * list);

listElement_t * get_linkedList_element(linkedList_t * list, int index);

int delete_from_linkedList(linkedList_t * list, int index);
int add_to_linkedList     (linkedList_t * list, int index, void * newData, size_t bytes);

void print_all_from_linkedlist(linkedList_t * list);

#endif
