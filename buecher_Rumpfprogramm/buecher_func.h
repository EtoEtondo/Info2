#ifndef BUECHER_FUNC_H
#define BUECHER_FUNC_H
/***********************************************************************
 * buecher_func.h
 * Headerfile der Sammlung von Funktionen zur Bücherlisten-Verwaltung
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* Struktur einer Autor-Definition */
typedef struct {
   char *name;                   /* Zeiger auf vollstdg. Namen dieses Autors */
   List_t buecher;
} Autor;

/* Struktur einer Verlag-Definition */
typedef struct {
   char *name;                   /* Zeiger auf vollstdg. Namen dieses Verlags */
   List_t buecher;
} Verlag;

/* Struktur einer Buch-Definition */
typedef struct {
   char *titel;                     /* Zeiger auf Titelstring */
   Autor *autor;                    /* Zeiger auf Element des Autoren-arrays */
   Verlag *verlag;                  /* Zeiger auf Element des Verlage-arrays */
   unsigned short erscheinungsjahr; /* Jahreszahl 4-stellig, z. B.: 2009 */
   char *isbn;                      /* Zeiger auf ISBN-string */
} Buch;


void buecher_read(FILE *infile, List_t buecher, List_t autoren, List_t verlage);
/* Liest das komplette Eingabe-file zeilenweise von (bereits
 * geöffnetem) infile ein */


void buch_add(char linebuf[], List_t buecher, List_t autoren, List_t verlage);

void buecher_print(List_t buecher);
/* Iteriert über Bücherliste zur Ausgabe */

void buch_print(const Buch *b);
/* Gibt ausgewählte Attribute eines Buches formatiert aus */

Autor *autor_link(const char *autorname, List_t autoren);

Verlag *verlag_link(const char *verlagname, List_t verlage);

int cmp_anz1(const void *a, const void *b);

int cmp_anz2(const void *a, const void *b);

int cmp_name_autor(const void *d1, const void *d2);

int cmp_name_verlag(const void *d1, const void *d2);

void top20printV(List_t verlage,const int NUMTOP);

void top20printA(List_t autoren,const int NUMTOP);

void* List_delete(List_t l, void *key, int (*cmp)(const void *e1, const void *e2));

#endif
