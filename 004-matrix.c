#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int rows;
  int cols;
  double * data;
} matrix;

/*
  1 2 3
  4 5 6
 
 
  => 2, 3; {123456}
 */

void printMat (matrix A) {
  if (A.data == NULL) {
    printf("Fehler\n");
    return;
  }
  
  for   (int r=0; r<A.rows; r++) {
    for (int c=0; c<A.cols; c++) {
      printf("%lf ", A.data[r * A.cols + c]);
    }
    printf("\n");
  }
}

matrix matMul (matrix A, matrix B) {
  matrix reVal = {0, 0, NULL};
  
  if (A.cols != B.rows) {
    printf("Fehler\n");
    return reVal;
  }
  
  reVal.rows = A.rows;
  reVal.cols = B.cols;
  reVal.data = calloc(reVal.rows * reVal.cols, sizeof(double));
  
  for     (int r=0; r<reVal.rows; r++) {
    for   (int c=0; c<reVal.cols; c++) {
      for (int k=0; k<    A.cols; k++) {
        reVal.data[r * reVal.cols + c] += A.data[r * A.cols + k] * B.data[k * B.cols + c];
      }
    }
  }
  
  return reVal;
}

int main () {
  matrix A, B, C;
  
  A.rows = 4;
  A.cols = 2;
  A.data = malloc(A.rows * A.cols * sizeof(double));
  
  for (int i=0; i<A.rows * A.cols; i++) {
    A.data[i] = i + 1;
  }
  
  
  B.rows = 2;
  B.cols = 3;
  B.data = malloc(B.rows * B.cols * sizeof(double));
  
  for (int i=0; i<B.cols; i++) {
    B.data[0 * B.cols + i] = 3 - i;
  }
  
  for (int i=0; i<B.cols; i++) {
    B.data[1 * B.cols + i] = 5 + i;
  }
  
  printMat(A);
  printf("\n");
  printMat(B);
  printf("\n");
  
  C = matMul(A, B);
  printMat(C);
  
  free(A.data);
  free(B.data);
  free(C.data);
}
