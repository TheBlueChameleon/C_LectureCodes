/* mergesort.c
 * example implementation of the recursive mergesort for integers
 */

// ========================================================================== //
// dependencies

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// ========================================================================== //
// macros

#define SWAP(x,y)           { x = x + y; y = x - y; x = x - y; }

#define RAND01              ( rand() / (double)(RAND_MAX) )
#define RANDBETWEEN(lo, hi) ( (lo) +  RAND01 * ((hi) - (lo)) )

// ========================================================================== //
// procs

int * get_rnd_field_int_between (unsigned int elements, int lo, int hi) {
  int * reVal = malloc(elements * sizeof(int));
  if (!reVal) {
    printf("Could not allocate memory.\n");
    exit(-1);
  }

  for (unsigned int i=0; i<elements; ++i) {
    reVal[i] = RANDBETWEEN(lo, hi);
  }

  return reVal;
}
// .......................................................................... //
void print_field_int (int * field, unsigned int elements) {
  for (unsigned int i=0u; i < elements -1; ++i) {
    printf(" %d,", field[i]);
  }
  printf(" %d\n", field[elements -1]);
}
// .......................................................................... //
int is_sorted_int  (int  * field, unsigned int elements) {
  for (unsigned int i = 0; i < elements-1; ++i) {
    if (field[i] > field[i+1]) {return 0;}
  }
  return 1;
}
// .......................................................................... //
void mergesort_int (int * field, unsigned int elements) {
  if (is_sorted_int(field, elements)) {return;}                                 // nothing to do here!

  if        (elements == 1) {                                                   // trivial field: always sorted
    return;

  } else if (elements == 2) {                                                   // 2-element-field: nonrecursive sorting
    if (field[0] > field[1]) {SWAP(field[0], field[1]);}
    return;

  } else {                                                                      // the core algorithm
    // split field into halves; first field is smaller for odd-sized fields
    unsigned int subfield_size = elements / 2;

    // sort subfields
    mergesort_int(field                ,            subfield_size);
    mergesort_int(field + subfield_size, elements - subfield_size);

    // merge the sorted subfields:
    unsigned int  idx_1 = 0,
                  idx_2 = 0;

    int * dummy = malloc(elements * sizeof(*dummy));                            // merge presorted arrays into this field
    if (!dummy) {
      printf("Could not allocate memory.\n");
      exit(-1);
    }


    unsigned int i;
    for (i = 0; i < elements; ++i) {

      if (idx_1 == subfield_size) {
        /* we've used up all "left array elements".
         * all items left for the merger are in the "right array", which goes
         * by the handle field
         * ==> we don't need to copy them to dummy and back to the same position
         *      where we found them in the first place!
         * ==> spare ourselves the copying and be done with!
         */

        break;
      }

      if (idx_2 == elements - subfield_size) {
        /* here we've used up the "right array elements". This means that we
         * need to take care of the "left array elements". However, they are
         * NOT in the correct spots in the final array 'field'
         * ==> copy them in one step
         */

        memcpy(dummy + i,
               field + idx_1,
               (subfield_size - idx_1) * sizeof(*dummy)
        );
        idx_1 = subfield_size;
        break;
      }

      /* now we can deal with the most common case: we have both, elements in
       * the left and the right list.
       * ==> pick the list with the correct item and copy it over to dummy
       */

      if (field[idx_1] <= field[subfield_size + idx_2]) {
        dummy[i] = field[idx_1];
        ++idx_1;

      } else {
        dummy[i] = field[subfield_size + idx_2];
        ++idx_2;
      }

    }

    // copy back to productive field:
    memcpy(field, dummy, (idx_1 + idx_2) * sizeof(*dummy));

    free(dummy);
  }

}

// ========================================================================== //
// main

int main () {
  srand(time(NULL));

  unsigned int field_size = 5;
  int *        field_elements = get_rnd_field_int_between(field_size, 5, 15);


  printf("before sorting:\n");
  print_field_int(field_elements, field_size);


  mergesort_int(field_elements, field_size);


  printf("after sorting:\n");
  print_field_int(field_elements, field_size);

  free(field_elements);
}
