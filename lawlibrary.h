#include <stdlib.h>
#include <time.h>

int getNewCase() {
	srand(time(NULL));
	return 1 + rand() % 255;
}

int checkActusReus(int Fall_ID) {return 1 + rand() % 255;}
	
int checkMensRea  (int Fall_ID) {return 1 + rand() % 255;}
int checkDefense  (int Fall_ID) {return 1 + rand() % 255;}