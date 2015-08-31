#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <limits.h>


// Globale Variablen fuer die Bestenliste
int scores[10];
char names[256*10];


/*
Oeffnet eine Datei mit dem Namen "name"
"mode" legt den Modus, in dem die Datei geoeffnet werden soll, fest
Rueckgabe: File-Handle zur geoeffneten Datei, NULL im Fehlerfall
*/
FILE* openFile(char* name, const char *restrict mode) {
  char dateiName[256];
  FILE *datei = NULL;
  if (name == NULL) return NULL;
  else strncpy(dateiName, name, 255*sizeof(char));
  if ((datei=fopen(dateiName,mode)) == NULL) {
    printf("Fehler beim Oeffnen der Datei \"%s\" mit Modus \"%s\"!\n", name, mode);
  }
  return datei;
}


/*
Lesen der Bestenliste aus Datei
Diese besteht aus 20 Zeilen - 10 mal je eine Zeichenkette ohne Leerzeichen und eine Ganzzahl
Diese werden abwechselnd in ein Zeichen-Array und ein Integer-Array gelesen
Gibt "false" im Fehlerfall zurueck, "true" sonst
*/
bool readHoF (char* name) {
  FILE* datei = openFile(name, "r+");
  if (datei == NULL) return false;

  // lese Datei zeilenweise ein
  for (int i=0; i<10; i++) {
    int score = 0;
    char line[256];

    // Namen aus Datei einlesen
    fgets(&names[i*256], 256, datei);

    // Anz. d. Rateversuche lesen, parsen und speichern
    fgets(line, 256, datei);
    sscanf(line, "%d\n", &score);
    scores[i] = score;
  }

  // ersetzt alle Vorkommen von \n durch \0
  // -> Terminierung der einzelnen Strings
  for (int j=0; j<2560; j++){
    if (names[j] == '\n') names[j] = '\0';
  }

  // Datei schliessen und Ende
  fclose(datei);
  return true;
}


/*
Schreiben der Bestenliste in Datei
Schreibt die Namen und Zahlen abwechselnd in die angegebene Datei
Gibt "false" im Fehlerfall zurueck, "true" sonst
*/
bool writeHoF (char* name) {
  FILE* datei = openFile(name, "w+");
  if (datei == NULL) return false;

  for (int i=0; i<10; i++) {
    // Namen schreiben
    // -> Schreibt bis \0
    fputs(&names[i*256], datei);
    // Zeilenumbruch
    fputs("\n", datei);
    // Anz. d. Rateversuche und Zeilenumbruch
    fprintf(datei, "%d\n", scores[i]);
  }

  fclose(datei);
  return true;
}


/*
Formatierte Ausgabe der Bestenliste
*/
void printHoF() {
  printf("Bestenliste\n");
  for(int i=0; i<10; i++) {
    printf("%5d ", i+1);
    printf("%25s", &names[i*256]);
    printf(" %8d\n", scores[i]);
    printf("------------------------------------------------\n");
  }
}


/*
Ueberprueft, ob man mit einer bestimmten Anzahl von Rateversuchen einen
Platz in er Bestenliste erreicht hat und gibt diesen dann zurueck.
-1, wenn man nicht drin ist.
*/
int checkHoF (int anzahl) {
  int platz = -1;
  for (int i=0; i<10; i++) {
    int tmp = scores[i];
    if (scores[i] == 0) tmp = INT_MAX;
    if (anzahl <= tmp) {
      printf("Platz %d in der Bestenliste erreicht!\n", i+1);
      platz = i;
      break;
    }
  }
  return platz;
}


/*
Fuegt einen neuen Eintrag in die Bestenliste ein.
Dazu muessen die Eintraege des Arrays dahinter um je eine Position
nach hinten ruecken. Der letzte Eintrag fliegt raus.
*/
void addToHoF (int platz,int anzahl) {
  
  // Platz fuer neuen Eintrag schaffen
  for (int i=9; i>=platz; i--) {
    scores[i] = scores[i-1];
    for (int j=0; j<256; j++) {
      if (!(names[256*(i-1)+j]=='\n') && !(names[256*(i-1)+j]==' ')) {
        names[i*256+j] = names[256*(i-1)+j];
      }
    }
  }
  
  // Anz. d. Rateversuche speichern
  scores[platz]=anzahl;
  
  // Namen einlesen und speichern
  printf("Name: ");
  getchar();
  int c, pos = 0;
  while (pos < 255 && (c=getchar()) != '\n') {
    names[platz*256+pos] = c;
    pos++;
  }
  
  // Zeilenende durch Terminierungszeichen ersetzen
  names[platz*256+pos] = '\0';
  
  // stdin-Puffer ggf. noch leeren
  while (c != '\n' && c != EOF) c = getchar();
}


/*
Die eigentliche Ratefunktion
Laesst den Nutzer solange raten, bis er die Zahl gefunden hat.
Zurueckgegeben wird die Anzahl der Versuche
*/
int raten (int gedachtezahl) {
  
  int ratemal = 0;
  int anzahl = 0;
  do {
    anzahl++;
    printf("Versuch %3d: Deine Zahl? ",anzahl);
    
    // Zahl von stdin einlesen
    while (scanf("%3d", &ratemal) <= 0) {
      printf("Fehler bei der Eingabe. Bitte versuche es noch einmal: ");
      // stdin-Puffer ggf. noch leeren
      int c = getchar();
      while (c != '\n' && c != EOF) c = getchar();
    }
    
    // Hinweise geben
    if (gedachtezahl > ratemal) {
      printf("Die gedachte Zahl ist groesser.\n");
    } else if (gedachtezahl < ratemal) {
      printf("Die gedachte Zahl ist kleiner.\n");
    } else if (gedachtezahl == ratemal) {
      printf("Super! Erraten mit %d Versuchen.\n",anzahl);
    }
    
  } while(!(gedachtezahl==ratemal));
  
  // Anzahl der benoetigten Rateversuche zurueck geben
  return anzahl;
}


/*
Ausgabe der zu erratenden Zahl und der Versuche in eine Logdatei
Gibt "false" im Fehlerfall zurueck, "true" sonst
name: Name der Log-Datei
r   : zu ratende Zahl
a   : Anz. d. Rateversuche
*/
bool writeToLog (char* name, int r, int a) {
  FILE* datei = openFile(name, "a");
  if (datei == NULL) return false;
  fprintf(datei,"Zahl: %d\nVersuche: %d\n--\n", r, a);
  fclose(datei);
  return true;
}


/*
Main
*/
int main(void) {

  int a, r, platz, nocheinmal = 0;

  // Einlesen der Bestenliste aus "hof.txt"
  if (!readHoF("hof.txt")) {
    printf("Fehler. Datei hof.txt konnte nicht eingelesen werden.\n");
  }

  do {
    // Zufallszahlengenerator initialisieren
    int stime;
    long ltime;
    ltime = time(NULL);
    stime = (unsigned) ltime/2;
    srand(stime);

    // Zufallszahl erzeugen und Spiel beginnen
    printf("Der Computer denkt sich eine Zahl zwischen 1 und 100.\n");
    r = (rand() % 100 + 1);
    a = raten(r);

    // Bestenliste
    printHoF();
    platz = checkHoF(a);
    if (platz > -1) {
      addToHoF(platz,a);
      printHoF();
    }

    printf("Nocheinmal? (1 fuer ja, 0 fuer nein) ");
    scanf("%d", &nocheinmal);

    // Ausgabe des Ergebnisses in "log.txt"
    if (!writeToLog("log.txt",r,a)) {
      printf("Fehler. Datei Log-Datei log.txt konnte nicht geschrieben werden.\n");
      return -2;
    }
  } while (nocheinmal != 0);

  // hof.txt schreiben
  if (!writeHoF("hof.txt")) {
    printf("Fehler. \"Hall of fame\" konnte nicht in hof.txt geschrieben werden.\n");
    return -4;
  }

  return 0;
}
