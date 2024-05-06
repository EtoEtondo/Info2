/***********************************************************************
 * buecher_func.c
 * Sammlung von Funktionen zur Bücherlisten-Verwaltung
 ***********************************************************************/

#include "buecher_func.h"
#include "list.h"

/***********************************************************************/

void buecher_read(FILE *infile, List_t buecher, List_t autoren, List_t verlage) {
   /* Liest das komplette Eingabe-file zeilenweise von (bereits
    * geöffnetem) infile ein */

   enum { MAXLL = 240};   /* max. input line length */
   char c, linebuf[MAXLL]; /* Einlesepuffer für eine Zeile */

   fgets(linebuf, sizeof(linebuf), infile); /* 1x Kopfzeile ueberlesen */

   /* Schleife ueber alle Bücher-Datensätze, speichern */
   while (fgets(linebuf, sizeof(linebuf), infile)) {

      /* Zeilenlänge absichern */
      if (linebuf[strlen(linebuf) - 1] != '\n') {   /* Zeile zu lang! */
         fprintf(stderr,
                 " *** Hinweis: Zeile auf der Datei zu lang (>%d)! ", MAXLL);
         fprintf(stderr, "Diese Zeile ignoriert:\n *** >%s...<\n", linebuf);
         while ((c = fgetc(infile)) != EOF) { /* Rest der überlangen Zeile ... */
            if (c == '\n') break;             /* ... überlesen bis NL od. EOF  */
         }
         continue;   /* diesen (unvollständigen) Buch-Datensatz ignorieren */
      }

      /* dieses Buch mit Verweisen auf Autor und Verlag speichern */
      buch_add(linebuf, buecher, autoren, verlage);
   }

}

/***********************************************************************/

void buch_add(char linebuf[], List_t buecher, List_t autoren, List_t verlage) {
   /* Erhält die eingelesene Eingabezeile eines Buch-Datensatzes,
    * zerlegt diese am Trennzeichen in die Attribute und speichert diese.
    * In der Buch-Struktur werden Zeiger auf dessen Autor- und Verlag-
    * Element gespeichert.
    */

   const char *delim = ";\n";    /* CSV-Trennzeichen + NL! */
   char *autorname, *verlagname;
   Buch *b = (Buch *) malloc(sizeof(Buch));

   /* Zeile zerlegen und Teile speichern */
   /* Titel;Autor;Verlag;Erscheinungsjahr;ISBN */
   b->titel            = strdup(strtok(linebuf, delim));
   autorname           = strtok(NULL, delim);
   verlagname          = strtok(NULL, delim);
   b->erscheinungsjahr = atoi(strtok(NULL, delim));
   b->isbn             = strdup(strtok(NULL, delim));

   /* Autor im bisherigen Autoren-Feld suchen, ggfs. neu anlegen,
    * pointer darauf im akt. Buch speichern */
   b->autor = autor_link(autorname, autoren);

   /* Verlag im bisherigen Verlage-Feld suchen, ggfs. neu anlegen,
    * pointer darauf im akt. Buch speichern */
   b->verlag = verlag_link(verlagname, verlage);

   List_add(b->verlag->buecher, b);
   List_add(b->autor->buecher, b);
   List_add(buecher, b);
}

/************************************************************************/
Autor *autor_link(const char *autorname, List_t autoren){
	Autor *autor= (Autor*) malloc(sizeof(*autor));
	autor->name = strdup(autorname);
	Autor *ascur = List_search(autoren, autor, cmp_name_autor);
	if(ascur==NULL){   		//Autor nicht existend
        List_add(autoren, autor);       //Autor hinzufügen
        autor->buecher= List_new();
	return autor;
      	}else{
        free(autor);
        return ascur;   //Autor struct muss zurückgeliefert werden
      }

}

Verlag *verlag_link(const char *verlagname, List_t verlage){
	Verlag *verlag= (Verlag*) malloc(sizeof(*verlag));
	verlag->name = strdup(verlagname);
	Verlag *vscur = List_search(verlage, verlag, cmp_name_verlag);
	if(vscur==NULL){   		//Verlag nicht existend
        List_add(verlage, verlag);       //Verlag hinzufügen
        verlag->buecher= List_new();
	return verlag;
      	}else{
        free(verlag);
        return vscur;   //Verlag struct muss zurückgeliefert werden
      }
}

/***********************************************************************/

void buecher_print(List_t buecher) {
   /* Iteriert über Bücherliste zur Ausgabe */

   unsigned int i = 0;
   printf("Bücherliste:\n");
   LIter_t iter = List_iterator(buecher);
   if(iter == NULL) return;
   while(LIterator_hasNext(iter)){
   printf("%5d: ", ++i);
   buch_print((Buch*) LIterator_next(iter));
   }
   LIterator_free(iter);
   printf("\n");
}

/***********************************************************************/

void buch_print(const Buch *b) {
   /* Gibt ausgewählte Attribute eines Buches formatiert aus */

   printf("[%10s] %s (%d): %s\n", b-> isbn,
          (b->autor != NULL ? b->autor->name : "*unbekannt*"),
          b->erscheinungsjahr, b->titel);
}

/***********************************************************************/

int cmp_anz1(const void *pt1, const void *pt2){
Verlag* a = *(Verlag**)pt1;
Verlag* b = *(Verlag**)pt2;
	return (List_length(b->buecher)-List_length(a->buecher));
}

/***********************************************************************/

int cmp_anz2(const void *pt1, const void *pt2){
Autor* a = *(Autor**)pt1;
Autor* b = *(Autor**)pt2;
	return (List_length(b->buecher)-List_length(a->buecher));
}

/************************************************************************/

void top20printV(List_t verlage ,const int NUMTOP){
   int i = 0, z;
   char *name;
    int anz_v = List_length(verlage);

   Verlag* anz1[anz_v];
   LIter_t itv = List_iterator(verlage);
   while(LIterator_hasNext(itv)){	
      anz1[i] = LIterator_next(itv);
      i++;
   }
   LIterator_free(itv);
   qsort(anz1, anz_v, sizeof(anz1[0]), cmp_anz1);

   for (i = 0; i < NUMTOP; i++) {
	z= List_length(anz1[i]->buecher);
	name= strdup(anz1[i]->name);
      printf("%3d: (%3d) %s\n", i + 1, z, name);
      buecher_print(anz1[i]->buecher);
   }
   
}

/************************************************************************/

void top20printA(List_t autoren,const int NUMTOP){
   int i = 0;
   int z;
   char *name;
   int anz_a = List_length(autoren);

   Autor* anz2[anz_a];
   LIter_t ita = List_iterator(autoren);
   while(LIterator_hasNext(ita)){	                                                    
      anz2[i] = LIterator_next(ita);
      i++;
   }
   LIterator_free(ita);
   qsort(anz2, anz_a, sizeof(anz2[0]), cmp_anz2);

   for (i = 0; i < NUMTOP; i++) {
	z= List_length(anz2[i]->buecher);
	name= strdup(anz2[i]->name);
      printf("%3d: (%3d) %s\n", i + 1, z, name);
      buecher_print(anz2[i]->buecher);
   }
}

/****************************************************************************************/

int cmp_name_autor(const void *x, const void *y){

      Autor* a; 
      Autor* b;
      a = (Autor*) x;
      b = (Autor*) y;
      return strcmp(a->name, b->name);                
}

int cmp_name_verlag(const void *x, const void *y){   
      Verlag* a;
      Verlag* b;
      a = (Verlag*) x;
      b = (Verlag*) y;
      return strcmp(a->name, b->name);
}

/******************************************************************************************/

int show_menu(char *menu_entries[], const int num_entries) {
   /* gibt Menu auf stdout aus,
    * liefert Nummer des selektierten Menüeintrags (0=Ende) */

   int i;
   char c;
   int sel;          /* Menüauswahl */
   int selOK = 0;    /* Flag, ob Selektion gültig */

   /* Menü ausgeben (ggfs. wiederholt, bis Selektion im gültigen Bereich) */
   while (! selOK) {

      printf("\n=== Menueauswahl ===\n");
      for (i = 0; i < num_entries; i++) {
         printf(" -%d- %s\n", i + 1, menu_entries[i]);
      }
      printf(" -0- Beenden\n");
      printf("Ihre Auswahl [0-%d]: ", num_entries);

      /* einen Integer lesen und prüfen */
      if (scanf("%d", &sel) == 1) {
         selOK = sel >= 0 && sel <= num_entries;
      }

      /* evtl. restl. (ungültige) Eingabe auf der Zeile überlesen */
      while ((c = getchar()) != EOF) {
         if (c == '\n') break;
      }

      if (! selOK) printf("*** Ungueltige Eingabe!\n");
   }
   printf("\n");

   /* gültige Selektion zurückgeben */
   return sel;
}

