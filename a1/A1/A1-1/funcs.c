#include "funcs.h"

void zahlen_erzeugen(int array[], const int UG, const int OG, const int LEN) {
    int i;
    srand(time(NULL));
    for (i=0; i<LEN; i++) {
        array[i] = (rand()%(OG-UG+1)+UG);
    }
}

void zahlen_ausgeben(int array[], int OG, const int LEN, const int ZPZ) {
    int i, x=0;
    double a;
    a = log10((double)OG)+1;
    for(i=0; i<LEN; i++) {
        printf("%*d ", (int) a, array[i]);
        x++;
        if(x%ZPZ == 0)
            printf("\n");
    }
}

void zahlen_ausgeben_inv(int array[], int OG, const int LEN, const int ZPZ) {
    int i, x=0;
    double a;
    a = log10((double)OG)+1;
    for(i=LEN-1; i>=0; i--) {
        printf("%*d ", (int) a, array[i]);
        x++;
        if(x%ZPZ == 0)
            printf("\n");
    }
}

int cmp(const void *p1, const void *p2) {
    return *((int*)p1) - *((int*)p2);
}
