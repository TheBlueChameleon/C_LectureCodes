// ========================================================================== //
// dependencies

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========================================================================== //
// definitions

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

typedef struct {
  char   firstName [20];
  char   lastName  [20];
  char   department[20];
  double salary;
} employee_t;


linkedList_t * make_linkedList ();
void           free_linkedList(linkedList_t * list);

listElement_t * get_linkedList_element(linkedList_t * list, int index);

int delete_from_linkedList(linkedList_t * list, int index);
int add_to_linkedList     (linkedList_t * list, int index, void * newData, size_t bytes);

void print_all_from_linkedlist(linkedList_t * list);


// ========================================================================== //
// management of linkedlist

// -------------------------------------------------------------------------- //
// constructor and destructor

linkedList_t * make_linkedList () {
  linkedList_t * reVal = malloc(sizeof(*reVal));
  if (!reVal) {
    printf("Fehler: Speicher konnte nicht alloziert werden\n");
    return NULL;
  }
  
  reVal->first        = NULL;
  reVal->size         = 0;
  reVal->printElement = NULL;
  
  return reVal;
}

// .......................................................................... //

void free_linkedList(linkedList_t * list) {
  while (list->size) {
    delete_from_linkedList(list, 0);
  }
  
  free(list);
}

// -------------------------------------------------------------------------- //
// index access

listElement_t * get_linkedList_element(linkedList_t * list, int index) {
  if (index < 0 || index >= list->size) {
    printf("Fehler: ungültiger Index\n");
    return NULL;
  }
  
  listElement_t * element = list->first;
  for (int i=0; i<index; i++) {
    element = element->next;
  }
  
  return element;
}

// -------------------------------------------------------------------------- //
// add and delete

int delete_from_linkedList(linkedList_t * list, int index) {
  if (index < 0 || index >= list->size) {
    printf("Fehler: ungültiger Index\n");
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
  if (prev) {prev->next = next;}
  
  if (list->memoryAutoManaged) {free(self->data);}
  free(self);
  
  return --list->size;
}

int add_to_linkedList(linkedList_t * list, int index, void * newData, size_t bytes) {
  if (index < 0 || index > list->size) {
    printf("Fehler: ungültiger Index\n");
    return -1;
  }
  
  listElement_t * prev, * self, * next;
  
  
  self = malloc(sizeof(*self));
  if (!self) {
    printf("Fehler: Speicher konnte nicht alloziert werden\n");
    return -1;
  }
  
  if (list->memoryAutoManaged) {
    self->data = malloc(bytes);
    if (!self->data) {
      printf("Fehler: Speicher konnte nicht alloziert werden\n");
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

// -------------------------------------------------------------------------- //
// screen output

void print_all_from_linkedlist(linkedList_t * list) {
  listElement_t * element = list->first;
  while (element != NULL) {
    list->printElement(element->data);
    element = element->next;
  }
}

// ========================================================================== //
// employee utilities

void printEmployee(void * employee) {
  printf("%20s | %20s | %20s | %8.2lf\n",
    ((employee_t *) employee)->firstName,
    ((employee_t *) employee)->lastName,
    ((employee_t *) employee)->department,
    ((employee_t *) employee)->salary
  );
}


// ========================================================================== //
// Main code

int main () {
  linkedList_t * list = make_linkedList();
  
  list->memoryAutoManaged = 0;
  list->printElement = printEmployee;
  
  employee_t * emp = malloc(sizeof(*emp));
    strcpy(emp->firstName , "Vanessa");
    strcpy(emp->lastName  , "Schmetterling");
    strcpy(emp->department, "Betriebsarzt");
    emp->salary     = 7000.0;
  add_to_linkedList(list, 0, emp, sizeof(employee_t));
  
  emp = malloc(sizeof(*emp));
    strcpy(emp->firstName , "Rebecka");
    strcpy(emp->lastName  , "Rein");
    strcpy(emp->department, "R&D");
    emp->salary     = 420.69;
  add_to_linkedList(list, 0, emp, 0);
  
  emp = malloc(sizeof(*emp));
    strcpy(emp->firstName , "Tina");
    strcpy(emp->lastName  , "Mauler");
    strcpy(emp->department, "Ethik-Kommission");
    emp->salary     = 9999.0;
  add_to_linkedList(list, 0, emp, 0);
  
  emp = malloc(sizeof(*emp));
    strcpy(emp->firstName , "ELiza");
    strcpy(emp->lastName  , "Carbos");
    strcpy(emp->department, "International Office");
    emp->salary     = 9876.0;
  add_to_linkedList(list, 0, emp, 0);
  
  emp = malloc(sizeof(*emp));
    strcpy(emp->firstName , "Ali");
    strcpy(emp->lastName  , "Berchan");
    strcpy(emp->department, "Marketing");
    emp->salary     = 6789.0;
  add_to_linkedList(list, 0, emp, 0);
  
  emp = malloc(sizeof(*emp));
    strcpy(emp->firstName , "Ce");
    strcpy(emp->lastName  , "Saurus");
    strcpy(emp->department, "Accounting");
    emp->salary     = 5555.0;
  add_to_linkedList(list, 0, emp, 0);
  
  printf(
    "%20s | %20s | %20s | %8s\n",
    "Vorname",
    "Nachname",
    "Abteilung",
    "Lohn"
  );
  printf(
    "---------------------+-"
    "---------------------+-"
    "---------------------+-"
    "--------\n"
  );
  
  print_all_from_linkedlist(list);
  
  list->memoryAutoManaged = 1;
  free_linkedList(list);
}
