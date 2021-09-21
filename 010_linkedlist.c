#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "010_linkedlist.h"

// ========================================================================== //
// constructor and destructor

linkedList_t * make_linkedList (int verbose) {
  linkedList_t * reVal = malloc(sizeof(*reVal));
  if (!reVal) {
    if (verbose) {printf("Fehler: Speicher konnte nicht alloziert werden\n");}
    return NULL;
  }
  
  reVal->first              = NULL;
  reVal->size               = 0;
  reVal->verbose            = verbose;
  reVal->memoryAutoManaged  = 0;
  reVal->printElement       = NULL;
  
  return reVal;
}

// .......................................................................... //

void free_linkedList(linkedList_t * list) {
  while (list->size) {
    delete_from_linkedList(list, 0);
  }
  
  free(list);
}

// ========================================================================== //
// index access

listElement_t * get_linkedList_element(linkedList_t * list, int index) {
  if (index < 0 || index >= list->size) {
    if (list->verbose) {printf("Fehler: ungültiger Index\n");}
    return NULL;
  }
  
  listElement_t * element = list->first;
  for (int i=0; i<index; ++i) {
    element = element->next;
  }
  
  return element;
}

// ========================================================================== //
// add and delete

int delete_from_linkedList(linkedList_t * list, int index) {
  if (index < 0 || index >= list->size) {
    if (list->verbose) {printf("Fehler: ungültiger Index\n");}
    return -1;
  }
  
  listElement_t * prev, * self, * next;
  
  if (index == 0) {
    prev = NULL;
    self = list->first;
    list->first = self->next;
    
  } else {
    prev = get_linkedList_element(list, index - 1);
    self = prev->next;
  }
  
  next = self->next;
  if (prev) {prev->next  = next;}
  else      {list->first = next;}
  
  if (list->memoryAutoManaged) {free(self->data);}
  free(self);
  
  return --(list->size);
}

// .......................................................................... //

int add_to_linkedList(linkedList_t * list, int index, void * newData, size_t bytes) {
  if (index < 0 || index > list->size) {
    if (list->verbose) {printf("Fehler: ungültiger Index\n");}
    return -1;
  }
  
  listElement_t * prev, * self, * next;
  
  
  self = malloc(sizeof(*self));
  if (!self) {
    if (list->verbose) {printf("Fehler: Speicher konnte nicht alloziert werden\n");}
    return -1;
  }
  
  if (list->memoryAutoManaged) {
    self->data = malloc(bytes);
    if (!self->data) {
      if (list->verbose) {printf("Fehler: Speicher konnte nicht alloziert werden\n");}
      free(self);
      return -1;
    }
    
    memcpy(self->data, newData, bytes);
    
  } else {
    self->data = newData;
  }
  
  if (index == 0) {
    prev = NULL;
    next = list->first;
    list->first = self;
    
  } else {
    prev = get_linkedList_element(list, index - 1);
    next = prev->next;
  }
  
  if (prev) {prev->next = self;}
  self->next = next;
  
  return ++list->size;
}

// ========================================================================== //
// screen output

void print_all_from_linkedlist(linkedList_t * list) {
  listElement_t * element = list->first;
  while (element != NULL) {
    list->printElement(element->data);
    element = element->next;
  }
}
