/* damit getopt() deklariert wird */
#define _POSIX_C_SOURCE 2

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <unistd.h>


/*
Konvertierungsfunktion
Ansatz, um die Komplexitaet bei der Implementierung zu begrenzen:
  1. Konvertiere gegebenen Temperaturwert in °C
  2. Konvertiere °C in Zielformat
Rueckgabe: konvertierter Temperaturwert
           FLT_MAX im Fehlerfall
*/
float convertTemp(char from, char to, float value) {
  
  // Rueckgabewert
  float ret = FLT_MAX;
  
  // konvertiere alle Angaben zu Celsius
  switch (from) {
    case 'C': // Celsius
      ret = value; // trivial
      break;
    case 'D': // Delisle
      ret = 100-value*2.0/3.0;
      break;
    case 'F': // Fahrenheit
      ret = (value-32.0)/1.8;
      break;
    case 'K': // Kelvin
      ret = value-273.15;
      break;
    case 'R': // Rankine
      ret = (value/1.8)-273.15;
      break;
    default: // Fehler: unbekanntes Format
      return FLT_MAX;
  }

  // konvertiere von Celsius in Zielformat
  switch (to) {
    case 'C':
      break; // trivial, nichts zu tun
    case 'D': // Fahrenheit
      ret = (100-ret)*1.5;
      break;
    case 'F': // Fahrenheit
      ret = ret*1.8+32.0;
      break;
    case 'K': // Kelvin
      ret = ret+273.15;
      break;
    case 'R': // Rankine
      ret = (ret+273.15)*1.8;
      break;
    default: // Fehler: unbekanntes Format
      return FLT_MAX;
  }

  // Ergebnis zurueck geben
  return ret;
}


/*
Ausgabe zur Hilfestellung
-> Hinweise zur Benutzung des Programms
*/
void printHilfe() {
  printf("Hinweise zur Benutzung des Programms\n");
  printf("Moegliche Optionen:\n");
  printf("  -v <temp>   : Zu konvertierende Temperatur (obligatorisch)\n");
  printf("  -f <einheit>: Einheit der angegebenen Temperatur (obligatorisch)\n");
  printf("  -t <einheit>: Einheit, in die die Temperatur konvertiert werden soll (obligatorisch)\n");
  printf("Unterstuetzte Einheiten:\n");
  printf("  C: Grad Celsius\n");
  printf("  D: Grad Delisle\n");
  printf("  F: Grad Fahrenheit\n");
  printf("  K: Kelvin\n");
  printf("  R: Grad Rankine\n");
}


/*
Main-Funktion
*/
int main(int argc, char *argv[]) {
  
  // Variablen fuer Quell- und Zieleinheit sowie Temperaturwert
  char *from, *to;
  from = NULL;
  to = NULL;
  float value = FLT_MAX;
  
  // Kommandozeilenparameter einlesen
  int ret;
  while ((ret=getopt(argc, argv, "f:t:v:")) != -1) {
    switch (ret) {
      case 'f':
         from = optarg;
         break;
      case 't':
         to = optarg;
         break;
      case 'v':
         value = atof(optarg);
         break;
      default:
        printHilfe();
        break;
    }
  }
  
  // Konvertierung durchfuehren und Ergebnis ausgeben
  if (from != NULL && to != NULL && value<FLT_MAX) {
    float temp = convertTemp(*from, *to, value);
    if (temp < FLT_MAX) {
      printf("%.2f°%c entsprechen %.2f°%c.\n", value, *from, convertTemp(*from, *to, value), *to);
    } else {
      // Fehler bei der Konvertierung
      printf("Fehler bei der Konvertierung! Quell- oder Zieleinheit unbekannt.\n");
      printHilfe();
      return -2;
    }
  } else {
    // Fehler: uns fehlt mindestens eine Angabe zur Konvertierung
    printf("Fehler. Du musst Quell- und Zieleinheit sowie einen Temperaturwert angeben!\n");
    printHilfe();
    return -1;
  }
  
  return 0;
}
