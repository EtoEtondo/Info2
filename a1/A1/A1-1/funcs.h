#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void zahlen_erzeugen(int array[], const int UG, const int OG, const int LEN);

void zahlen_ausgeben(int array[], int OG, const int LEN, const int ZPZ);

void zahlen_ausgeben_inv(int array[], int OG, const int LEN, const int ZPZ);

int cmp(const void *p1, const void *p2);

#endif
