/* F0X_main.c
 * compile with the following line
 * 
 * gcc -std=c11 -Wall -Wpedantic -Wimplicit-fallthrough 998_main.c 998_linkedlist.c -lm -o linkedlist
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "998_linkedlist.h"

// ========================================================================== //

typedef struct {
  char   firstName [20];
  char   lastName  [20];
  char   department[20];
  double salary;
} employee_t;

void printEmployee(void * employee) {
  printf("%20s | %20s | %20s | %8.2lf\n",
    ((employee_t *) employee)->firstName,
    ((employee_t *) employee)->lastName,
    ((employee_t *) employee)->department,
    ((employee_t *) employee)->salary
  );
}

// ========================================================================== //

int main () {
  linkedList_t * list = make_linkedList(1);                                     // verbose mode
  
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
