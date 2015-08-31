#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

/*
Oeffnet eine Datei mit dem Namen "name"
Falls name==NULL, erfrage Dateinamen per Kommandozeile
Rueckgabe: File-Handle zur geoeffneten Datei, NULL im Fehlerfall
*/
FILE* openFile(char* name) {
  char dateiName[256];
  FILE *datei = NULL;
  
  if (name == NULL) {
    printf("Bitte gib einen Dateinamen an: ");
    scanf("%s", dateiName);
  } else {
    strncpy(dateiName, name, 255*sizeof(char));
  }
  
  if ((datei=fopen(dateiName,"r")) == NULL) { 
    printf("Fehler beim Oeffnen der Datei!\n");
  }
  
  return datei;
}


/*
Liest eine Datei zeilenweise ein
-> Annahme: Ein float-Wert pro Zeile
-> Speicher fuer *retVal wird reserviert (spaeter freizugeben!)
-> Rueckgabe: Laenge des Feldes/Array, -1 im Fehlerfall
Achtung: Jede Zeile der Datei wird als Zahl interpretiert!
         Es wird keine Typenpruefung vorgenommen.
*/
int getFloatsFromFile(char *dateiName, float **retVal) {
  
  FILE* datei = openFile(dateiName);
  if (datei == NULL) return -1;
  char line[256];
  int anzZeilen = 0;
  
  // lese Datei zeilenweise ein
  while (fgets(line,256,datei) != NULL) {
    float temp;
    sscanf(line, "%f\n", &temp);
    // zusaetzlichen Speicher fuer neuen Eintrag reservieren
    *retVal = (float*) realloc(*retVal, (anzZeilen+1)*sizeof(float));
    (*retVal)[anzZeilen]= temp;
    anzZeilen++;
  }
  
  // Datei schliessen und die Anzahl der gelesenen Zeilen zurueck geben
  fclose(datei);
  return anzZeilen;
}


/*
Main
*/
int main(int argc, char *argv[]) {

  float max;
  char *dateiName = NULL;
  if (argc < 2) {
    // Kommandozeilenparameter kann Dateinamen der einzulesenden Datei enthalten
    printf("Achtung, keine zu oeffnende Datei als Parameter uebergeben.\n");
  } else {
    dateiName = argv[1];
    // weitere Uebergabewerte werden einfach ignoriert
  }

  // falls kein Dateiname per Kommandozeilenparameter uebergeben wurde,
  // erfragt die Funktion getFloatsFromFile einen Dateinamen von Benutzer
  float *floatArray = NULL;
  int anz = getFloatsFromFile(dateiName, &floatArray);

  // Maximum suchen
  // kanonischer Ansatz, da keine Annahme ueber die Sortierung der Eintraege gemacht werden kann
  if (anz > 0) {
    max = floatArray[0];
  } else {     // wenn anz <= 0, dann muss ein Fehler beim Einlesen der Zahlen aus der Datei vorliegen
    return -1; // Abbruch.
  }
  for (int i = 1; i < anz; i++) {
    if (floatArray[i] > max) max = floatArray[i];
  }
  if (anz > 0) printf("Das Maximum der %i gelesenen Zahlen ist %.2f.\n", anz, max);
  
  // aufraeumen und beenden
  if (floatArray != NULL) free(floatArray);
  return 0;
}
