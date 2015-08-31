#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int main (void) {

  // die zu ueberpruefende Zahl; eine Ganzzahl von 0 bis 18.446.744.073.709.551.615 (belegt 8 Bytes im Speicher)
  unsigned long long number = 0;
  // Prozess 1 testet von begin1 bis end1 und Prozess 2 von begin2 bis end2
  unsigned long long begin1,begin2 ,end1,end2;
  unsigned long long i = 0;
  bool isPrime = true;

  // Variablen zur Unterstuetzung der Interprozesskommunikation
  int v = 0;                   // v wird vom Kindprozess auf 1 gesetzt, falls ein Teiler gefunden wurde
  int ret_code = 0;            // Hilfsvariable zum Speichern von zurueckgegebenen Werten
  const int n = sizeof(int);   // die Laenge des Datentyps "int" in Bytes (hier: 4)
  char check[n];               // Hilfsfeld um int-Werte durch die Pipe zu uebertragen
  int fd[2];                   // Dateideskriptor zur Kommunikation mit dem Kindprozess
  pid_t pid = 0;               // Prozess-ID des Kindes

  // Variablen initialisieren
  begin1 = begin2 = end1 = end2 = 0;
  fd[0] = fd[1] = 0;
  check[0] = check[1] = check[2] = check[3] = 'x';

  // Zahl von der Konsole einlesen und in number speichern
  printf("Bitte gibt eine zu pruefende Zahl ein: ");
  while (scanf("%llu", &number) <= 0) {
    printf("Fehler bei der Eingabe. Bitte versuche es noch einmal: ");
    // stdin-Puffer ggf. noch leeren
    int c = getchar();
    while (c != '\n' && c != EOF) c = getchar();
  }
    
  /*
   * Die Prozesse arbeiten je von beginN bis endN
   * => number muss mindestens 4 sein, damit wir die Grenzen
   *    sinnvoll waehlen koennen
   * => Sonderbehandlung fuer alle Zahlen kleiner 4
   */
  printf("%llu ist... ", number);
  fflush(stdout);
  if (number == 0 || number == 1) {
    printf("keine Primzahl.\n");
    return EXIT_SUCCESS;
  } else if (number == 2 || number == 3) {
    printf("eine Primzahl.\n");
    return EXIT_SUCCESS;
  }

  // Gerade Zahlen koennen sofort als nicht-prim erkannt werden
  if (number % 2 == 0) {
    printf("keine Primzahl.\n");
    return EXIT_SUCCESS;
  }

  // Suchgrenzen festlegen
  // Suche bis sqrt(number) ist ausreichend!
  begin1 = 3;
  end1 = sqrt(number) / 2;
  begin2 = end1 + 1;
  end2 = sqrt(number) + 1;

  // Pipe, in die der Kindprozess sein Ergebnis schreibt, erzeugen
  ret_code = pipe(fd);
  if (ret_code < 0) {
    perror ("Fehler beim Einrichten der Pipe.");
    exit(EXIT_FAILURE);
  }

  /*
   * Zwei Prozesse, die den Test durchfuehren
   * => fork() um Kindprozess zu erstellen
   */
  pid = ret_code = fork();
  if (ret_code < 0) {
    perror ("Fehler bei fork().");
    exit(EXIT_FAILURE);
  }

  /*
   * Elternprozess
   */
  if (pid > 0) {

    // Schreibseite der Pipe schliessen
    close(fd[1]);

    // Test durchfuehren
    for (i = begin1; i <= end1; i += 2) { // gerade Teiler koennen wir bereits ausschliessen
      if (number % i == 0) { // Prueft, ob teilbar ohne Rest
        isPrime = false;
        break;
      }
    }

    // Warten auf den Kindprozess
    ret_code = waitpid(pid, NULL, 0);
    if (ret_code < 0) {
      perror ("Fehler beim Warten auf Kindprozess.");
      exit(EXIT_FAILURE);
    }

    // Ergebnis des Kindprozesses abholen und auswerten
    // - Aus Pipe lesen
    // - Zahl wieder aus den 4 Bytes zusammenbauen und pruefen, ob ungleich 0
    read (fd[0], check, n);
    if (((check[0]<<24)+(check[1]<<16)+(check[2]<<8)+check[3]) != 0) {
      isPrime=false;
    }

    // Endgueltiges Ergebnis ausgeben
    if (isPrime) printf("eine Primzahl.\n");
    else printf("keine Primzahl.\n");
  }

  /*
   * Kindprozess
   */
  else {
    // Leseseite der Pipe schliessen
    close(fd[0]);

    // mit ungeradem Teiler beginnen
    if (begin2 % 2 == 0) begin2++;
    for (i = begin2; i < end2; i += 2) {
      // Pruefen, ob teilbar ohne Rest (wie oben)
      if (number % i == 0) {
        v = 1;
        break;
      }
    }

    /* Das Ergebnis v der Berechnung in Pipe schreiben:
     * - wenn kein Teiler gefunden wurde, dann gitl v==0
     * - v==1, falls Teiler gefunden
     *
     * v ist vom Typ int, der 4 Byte lang ist.
     * Idee hier: schreibe die 4 Byte in ein Char-Array (ein Char ist 1 Byte gross)
     * >> : Bitshift nach rechts, immer ein Byte (8 bits) lang;
     * &  : bitweise Verknuepfung mit 0xFF
     */
    check[0] = (v >> 24) & 0xFF;
    check[1] = (v >> 16) & 0xFF;
    check[2] = (v >> 8) & 0xFF;
    check[3] = v & 0xFF;

    // In Pipe schreiben; gibt die Anzahl der geschriebenen Bytes zurueck
    ret_code = write(fd[1], check, n);
    if (ret_code != n) {
      perror ("Fehler bei write().");
      exit(EXIT_FAILURE);
    }
  }

  // Ende
  return EXIT_SUCCESS;
}
