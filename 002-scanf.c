#include <stdio.h>

int main () {
  char myText[101];
  int  number, first;
  
  printf("please provide an integer:\n");
  scanf("%d", &first);
  
  printf("please provide some text:\n");
  scanf(" %100[^\n]", myText);
  
  printf("please provide an integer:\n");
  scanf(" %d", &number);
  
  printf("number: %d\n", first);
  printf("text  : %s\n", myText);
  printf("number: %d\n", number);
}
