/* damit getopt() deklariert wird */
#define _POSIX_C_SOURCE 2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>


/*
Funktion, um die Anzahl der Nachbarn einer Zelle zu bestimmen
-> (xPos,yPos) geben die Zelle von Interesse an
-> xPos \in [0;breite-1]
-> yPos \in [0;hoehe-1]
Rueckgabe: Anzahl der Nachbar einer Zelle, <0 im Fehlerfall
*/
int getAnzNachbarn(int breite, int hoehe, bool *spielfeld, int xPos, int yPos) {
  
  // Koordinaten auf Gueltigkeit pruefen
  if (xPos >= breite || xPos < 0) return -1;
  if (yPos >= hoehe || yPos < 0) return -2;
  
  int n=0;
  // wir muessen alle Zellen im Raum xPos +/- 1 und yPos +/- 1 pruefen
  for (int b = -1; b <= 1; b++) {
    // befinden wir uns noch im Spielfeld
    // -> Randzellen beachten, damit wir unseren Speicherbereich nicht verlassen!
    if (xPos+b >= 0 && xPos+b < breite) {
      for (int h = -1; h <= 1; h++) {
        // befinden wir uns immernoch im Spielfeld
        if (yPos+h >= 0 && yPos+h < hoehe) {
          // die eigene Zelle darf nicht mitgezaehlt werden!
          if (!(b==0 && h==0) && spielfeld[(yPos+h)*breite+(xPos+b)]) n++;
        }
      }
    }
  }
  
  // Anzahl der gefundenen Nachbarn zurueckgeben
  return n;
}


/*
Berechne das neue Spielfeld
Rueckgabe:
  - false, falls weder eine Zelle geboren noch gestorben sein sollte, true sonst
  - Zweck: Erkennung, ob sich noch Aenderungen am Spielfeld ergeben -> Abbruchbedingung
*/
bool berechneNeuesSpielfeld(int breite, int hoehe, bool **spielfeld) {
  
  // Speicher fuer neues Spielfeld reservieren
  bool *neuesSpielfeld = NULL;
  neuesSpielfeld = (bool*) malloc(breite*hoehe*sizeof(bool));
  
  // neues Spielfeld berechnen
  // Regeln: (vgl. z.B. auch Wikipedia)
  //   Eine tote Zelle mit genau drei lebenden Nachbarn wird in der Folgegeneration neu geboren.
  //   Lebende Zellen mit weniger als zwei lebenden Nachbarn sterben in der Folgegeneration an Einsamkeit.
  //   Eine lebende Zelle mit zwei oder drei lebenden Nachbarn bleibt in der Folgegeneration lebend.
  //   Lebende Zellen mit mehr als drei lebenden Nachbarn sterben in der Folgegeneration an Ueberbevoelkerung.
  //   -> Hinweis: alle anderen Zellen leben nicht
  bool aenderung=false;
  for (int h = 0; h < hoehe; h++) {
    for (int b = 0; b < breite; b++) {
      int anzNachbarn = getAnzNachbarn(breite, hoehe, *spielfeld, b, h);
      // Fehlerbehandlung (sollte hoffentlich niemals eintreten)
      if (anzNachbarn < 0) {
       printf("Fehler bei der Berechnung der Anzahl der Nachbarn in Zelle (%i,%i)\n", b, h);
       printf("Abbruch der Berechnung.\n");
       return false;
      }
      // Iteration ueber alle Spielfelder
      // Implementierung gemaess der oben stehenden Spielregeln
      // kanonischer Ansatz, kann auch optimiert werden
      if (!(*spielfeld)[h*breite+b] && anzNachbarn==3) {
        neuesSpielfeld[h*breite+b] = true;
        aenderung = true; // tote Zelle wurde neu geboren
      } else if ((*spielfeld)[h*breite+b] && anzNachbarn<2) {
        neuesSpielfeld[h*breite+b] = false;
        aenderung = true; // lebende Zelle verstarb
      } else if ((*spielfeld)[h*breite+b] && (anzNachbarn==2 || anzNachbarn==3)) {
        neuesSpielfeld[h*breite+b] = true; // keine Aenderung, lebende Zelle lebt weiterhin
      } else if ((*spielfeld)[h*breite+b] && anzNachbarn>3) {
        neuesSpielfeld[h*breite+b] = false;
        aenderung = true; // lebende Zelle verstarb
      } else {
        // keine Aenderung, tote Zelle verweilt in ihrem Zustand
        neuesSpielfeld[h*breite+b] = false;
      }
    }
  }
  
  // altes Spielfeld loeschen/freigeben, Verweis auf neuesSpielfeld erstellen
  if (*spielfeld != NULL) free(*spielfeld);
  *spielfeld = neuesSpielfeld;
  return aenderung;
}


/*
Ausgabe eines Spielfeldes auf der Standardausgabe
*/
void printSpielfeld(int breite, int hoehe, bool *spielfeld) {
  for (int h = 0; h < hoehe; h++) {
    for (int b = 0; b < breite; b++) {
      if (spielfeld[h*breite+b]) printf("* ");
      else printf("- ");
    }
    printf("\n");
  }
}


/*
Ausgabe der Hilfestellung
-> Hinweise zur Benutzung des Programms
*/
void printHilfe() {
  printf("Hinweise zur Benutzung des Programms\n");
  printf("Moegliche Optionen:\n");
  printf("  -b <breite>: Lege die Breite des gewuenschten Spielfeldes auf <breite> fest (optional)\n");
  printf("  -h <hoehe> : Lege die Hoehe des gewuenschten Spielfeldes auf <hoehe> fest (optional)\n");
  printf("  -d <dichte>: Lege die gewuenschte Belegungsdichte (in %%) des Spielfeldes auf <dichte> fest (obligatorisch)\n");
}


/*
Main-Funktion
*/
int main(int argc, char *argv[]) {

  // Standardwerte
  int breite = 16;
  int hoehe  = 16;
  int belegungsDichte = INT_MAX; // definiert in limits.h
  
  // Kommandozeilenparameter einlesen
  int ret;
  while ((ret=getopt(argc, argv, "b:h:d:")) != -1) {
    switch (ret) {
      case 'b': // Breite des Spielfeldes
        breite = atoi(optarg);
        break;
      case 'h': // Hoehe des Spielfeldes
        hoehe = atoi(optarg);
        break;
      case 'd': // Belegungsdichte des Spielfeldes mit lebenden Zellen [%]
        belegungsDichte = atoi(optarg);
        break;
      default:
        printHilfe();
        break;
    }
  }
  
  // zumindest die Belegungsdichte muss von Nutzer angegeben worden sein!
  if (belegungsDichte == INT_MAX) {
    printf("Fehler. Es muss mindestens die gewuenschte Belegungsdichte des Spielfeldes angegeben werden.\n\n");
    printHilfe();
    return -1;
  } else if (belegungsDichte < 0) {
    printf("Feler. Die gewuenschte Belegungsdichte des Spielfeldes muss >= 0 sein.\n");
    return -2;
  } else if(belegungsDichte > 100) {
    printf("Hinweis: Ihre Eingabe der Belegungsdichte ist mit %i%% nicht sinnvoll.\n", belegungsDichte);
    printf("Eine maximale Belegungsdichte von 100%% wird impliziert.\n\n");
  }
  
  // Speicher fuer Spielfeld reservieren und zufaellig mit Zellen belegen
  bool *spielfeld = NULL;
  spielfeld = (bool*) malloc(breite*hoehe*sizeof(bool));
  
  // Zufallszahlengenerator initialisieren
  srand(time(NULL));
  // Spielfeld zufaellig belegen
  for (int h = 0; h < hoehe; h++) {
    for (int b = 0; b < breite; b++) {
      // gewuenschte Belegungsdichte honorieren
      if (rand()%100 < belegungsDichte) spielfeld[h*breite+b] = true;
      else spielfeld[h*breite+b] = false;
    }
  }

  int runde=0;
  bool aenderung = true;
  // solange sich Aenderungen am Zustand des Spielfeldes ergeben
  // berechnen wir das neue Spielfeld
  while (aenderung) {
    printf("Runde %i:", runde);
    if (runde==0) printf(" (Ausgangssituation)");
    printf("\n");
    printSpielfeld(breite, hoehe, spielfeld);
    printf("\n");
    aenderung = berechneNeuesSpielfeld(breite, hoehe, &spielfeld);
    runde++;
    // Eine Sekunde verzoegerung zur menschenlesbaren Ausgabe
    sleep(1);
  }
  
  // Spielfeld noch einmal ausgeben, um den Stillstand der Population zu zeigen
  printf("Keine Aenderungen mehr in Runde %i!\n", runde);
  printSpielfeld(breite, hoehe, spielfeld);
  
  // aufraeumen und Ende
  if (spielfeld != NULL) free(spielfeld);
  return 0;
}
