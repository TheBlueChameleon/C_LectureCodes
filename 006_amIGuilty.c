#include <stdio.h>
#include "lawlibrary.h"

int main (void) {
	int Fall_ID, Tatbestand, Rechtswidrigkeit, Schuldausschlussgrund;
	
	Fall_ID = getNewCase();
	
	Tatbestand            = checkActusReus(Fall_ID);
	Rechtswidrigkeit      = checkMensRea  (Fall_ID);
	Schuldausschlussgrund = checkDefense  (Fall_ID);
	
	if (Tatbestand && Rechtswidrigkeit && ! Schuldausschlussgrund) {
		printf("Schuldig!\n");
	} else {
		printf("Freispruch!\n");
	}
}
