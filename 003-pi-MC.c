#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double getPi (int N) {
  double reVal = 0;
  double x, y;
  
  for (int i=0; i<N; i++) {
    x = (double) rand() / RAND_MAX;
    y = (double) rand() / RAND_MAX;
    
    reVal += (hypot(x, y) < 1) ? 1 : 0;
  }
  
  return 4 * (reVal / N);
}

int main () {
  srand(time(NULL));
  
  printf( "%lf\n", getPi(1000) );
}
