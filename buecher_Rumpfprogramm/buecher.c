/***********************************************************************
 * buecher  (IN2, Übungsaufgabe 1)
 * Liest Buecherliste, erzeugt (statische) arrays
 * von Büchern, Autoren, Verlagen.
 * Gibt Bücherliste in Einlese-Reihenfolge und Top-20
 * (nach Anzahl der Bücher) der Autoren- und Verlageliste aus.
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#include "buecher_func.h"

enum{NUMTOP=5};

int main() {

   List_t buecher;
   List_t autoren;
   List_t verlage;
   if((buecher = List_new()) == NULL) return 0; //list buecher
   if((autoren = List_new()) == NULL) return 0; 
   if((verlage = List_new()) == NULL) return 0; 

   FILE *infile;              /* filepointer Eingabedatei */
   char infilename[] = "buecherliste.csv";


   /*************************************************************
    * Bücher-Datensätze einlesen und speichern
    *************************************************************/

   printf("\nBuecher-Liste\n");
   printf(  "=============\n\n");

   /* Eingabedatei oeffnen und pruefen */
   if ((infile = fopen(infilename, "r")) == NULL) {
      fprintf(stderr, " *** Fehler: Kann '%s' nicht zum Lesen oeffnen!\n",
              infilename);
      return 1;
   }

   /* alle Bücher-Datensätze einlesen */
   buecher_read(infile, buecher, autoren, verlage);

   /* Eingabedatei schliessen und Kontrollmeldung */
   fclose(infile);
   printf("Es wurden %d Buecher-Datensaetze\n", List_length(buecher));
   printf("aus %d unterschiedlichen Verlagen\n", List_length(verlage));
   printf("von %d unterschiedlichen Autoren eingelesen.\n\n", List_length(autoren));


   /*************************************************************
    * Ergebnis-Ausgabe
    *************************************************************/

   int i=0;
   int anz_a = List_length(autoren);
   int anz_v = List_length(verlage);

   printf("=== Eingelesene Buecher ===\n");
  

static char *menu_entries[] = {
      "Komplette Buecherliste ausgeben",
      "Top5-Autorenliste (mit Buechern) ausgeben",
      "Top5-Verlageliste ausgeben",
   };
   const int num_entries = sizeof(menu_entries) / sizeof(menu_entries[0]);
   int sel;         /* Menu-Auswahl */

   /* wiederholt Menü ausgeben bis '0=Beenden' gewählt */
   while ((sel = show_menu(menu_entries, num_entries))) {
      switch (sel) {
         case 1:
            printf(" --- Buecherliste\n");
 	    printf("=== Eingelesene Buecher ===\n");
	    buecher_print(buecher);
            break;
         case 2:
            printf(" --- Autorenliste\n");
            printf("=== Top%d Autoren sortiert nach Anzahl Buecher ===\n", NUMTOP);
   	    top20printA(autoren,NUMTOP);
            break;
         case 3:
            printf(" --- Verlageliste\n");
            printf("=== Top%d Verlage sortiert nach Anzahl Buecher ===\n", NUMTOP);
 	    top20printV(verlage,NUMTOP);
            break;
         default:
            printf(" *** inkonsistente Menueliste!\n");
      }
   }

   printf("Programm regulaer beendet.\n");
   return 0;

}
