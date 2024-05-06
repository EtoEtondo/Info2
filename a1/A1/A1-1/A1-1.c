#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcs.h"

int main() {
    
    enum {
        LEN =  500,  /* array-Länge */
        UG  =  100,  /* Untergrenze des Intervalls */
        OG  = 1000,  /* Obergrenze des Intervalls */
        ZPZ =   10,  /* Zahlen pro Zeile */
    };
    
    int zahlen[LEN];
    
    zahlen_erzeugen(zahlen, UG, OG, LEN);
    
    zahlen_ausgeben(zahlen, OG, LEN, ZPZ);
    
    qsort(zahlen, LEN, sizeof(zahlen[0]), cmp);
    
    printf("\n");
    
    zahlen_ausgeben(zahlen, OG, LEN, ZPZ);
    
    printf("\n");
    
    zahlen_ausgeben_inv(zahlen, OG, LEN, ZPZ);
    
    printf("\n");
    
    return 0;
    
}
