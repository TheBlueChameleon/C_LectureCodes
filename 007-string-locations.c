#include <stdio.h>

int main () {
  char * pointer = "code segment";
  char array[]   = "stack";

  printf("%s\n", pointer);
  printf("%s\n", array  );

  pointer[0] = 'C';       // this causes a segfault -- write access to code segment is not allowed!
  array  [0] = 'S';

  printf("%s", pointer);
  printf("%s", array  );

  pointer = "neu";        // okay
  // array   = "neu";        // does not even compile
}
