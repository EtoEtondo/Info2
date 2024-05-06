#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"


int main() {
    
    int i;
    char array[MAXL];
    char fname[] = "dict-american.txt";
    
    einlese_func(fname, array);
    
    for(i=0; i<30; i++) {
        puts(&array[i]);
    }
    
    return 1;
    
}
