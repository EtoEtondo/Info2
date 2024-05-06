/***********************************************************************
 * menu_demo
 * Demonstriert ein einfaches, aber portables, alfanumerisches Menu
 ***********************************************************************/
#include <stdlib.h>
#include <stdio.h>



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


int main() {

   /* Texte der Menüeinträge (ohne '0=Beenden') */
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
            /* TODO */
		buecher_print(buecher);
            break;
         case 2:
            printf(" --- Autorenliste\n");
            /* TODO */
            break;
         case 3:
            printf(" --- Verlageliste\n");
            /* TODO */
            break;
         default:
            printf(" *** inkonsistente Menueliste!\n");
      }
   }

   printf("Programm regulaer beendet.\n");
   return 0;
}
