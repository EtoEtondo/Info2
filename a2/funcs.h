#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void einlese_func(FILE *infile, char *woerter[], int *num_woerter, const int MAXWORT,
  const int MINZCHN);

void print_func(char *woerter[],int *num_woerter,const int NUMOUT);

int cmp_alph(const void *a, const void *b);

int cmp_c3(const void *a, const void *b);

int cmp_len(const void *a, const void *b);

#endif
