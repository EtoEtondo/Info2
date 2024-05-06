#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"


int main() {

enum{ MAXWORT = 250000, MINZCHN = 4, NUMOUT = 20,};
    
char *woerter[MAXWORT];
int num_woerter = 0;
FILE *infile;
char infilename[] = "dict-american.txt";

    if((infile=fopen(infilename, "r"))==NULL) {
        fprintf(stderr, "Datei konnte nicht gefunden und geöffnet werden!\n");
	return 1;
    }

einlese_func(infile, woerter, &num_woerter, MAXWORT, MINZCHN);
fclose(infile);
printf("Anz.Wörter: %d\n", num_woerter);

print_func(woerter, &num_woerter, NUMOUT);

qsort(woerter, num_woerter, sizeof(woerter[0]), cmp_alph);
printf("Alphabetisch:\n");
print_func(woerter, &num_woerter, NUMOUT);

qsort(woerter, num_woerter, sizeof(woerter[0]), cmp_c3);
printf("Dritter Buchstabe:\n");
print_func(woerter, &num_woerter, NUMOUT);

qsort(woerter, num_woerter, sizeof(woerter[0]), cmp_len);
printf("Länge:\n");    
print_func(woerter, &num_woerter, NUMOUT);
}
