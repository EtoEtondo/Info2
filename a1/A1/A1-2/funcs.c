#include "funcs.h"

void einlese_func(char *fname, char array[]) {
    
    FILE *fp;
    if((fp=fopen(fname, "r"))==NULL) {
        fprintf(stderr, "Datei konnte nicht gefunden und geöffnet werden!\n");
    }
    
    int i, arr_len = 0;
    for(i=0; i<MAXL; i++){
        fgets(array, LEN+1, fp);
        if(strlen(array) < MINLEN+1) {
            i-=1;
        }
        arr_len++;
    }

    if(arr_len == MAXL)
        printf("Array-Grenze erreicht: Es kann nichts mehr gespeichert werden!\n");
    
}

