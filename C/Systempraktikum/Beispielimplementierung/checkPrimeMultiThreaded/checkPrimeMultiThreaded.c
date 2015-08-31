#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include <gmp.h>

// Wir begrenzen die max. Anz. an Stellen pro Zahl aus naheliegenden Gruenden
#define MAXDIGITS 2048

// Anzahl der zu erzeugenden Threads
int ANZTHREADS = 4;

// globale Statusvariable als Abbruchbedingung fuer die Threads
bool found = false;

// globale Variablen: zu pruefende Zahl, Suchgrenzen der einzelnen Threads
mpz_t number, *anf, *ende;


/*
Funktion, die die zu pruefende Zahl ("number") auf moegliche Teiler prueft
- Diese Funktion wird von jedem Thread ausgefuehrt
- In *index wird die Ordnungsnummer des Threads uebergeben
- Mithilfe des *index greift der jeweilige Thread auf seinen Bereich der zu pruefenden Zahlen zu
  -> Globale Variablen *anf und *ende
*/
void *pruefeTeiler(void *index) {

  // Index des Threads uebernehmen
  int *i = (int*) index;

  // temporaerer Zwischenspeicher
  mpz_t temp;
  mpz_init(temp);
  // Zu pruefender Teiler fuer Schleife
  mpz_t teiler;
  mpz_init(teiler);

  // Teiler mit der ersten ungeraden Zahl belegen
  mpz_set(teiler, anf[*i]);
  if (mpz_mod_ui(temp, teiler, 2) == 0) mpz_add_ui(teiler, teiler, 1);

  do { // Teiler sequentiell pruefen
    mpz_mod(temp, number, teiler);
    if (mpz_sgn(temp) == 0) { // Teiler erfolgreich gefunden
      found = true;           // Abbruch der Schleife!
    } else {
      mpz_add_ui(teiler, teiler, 2);
      mpz_sub(temp, ende[*i], teiler);
    }
  } while (mpz_sgn(temp) >= 0 && !found);

  mpz_clear(temp);
  mpz_clear(teiler);
  return NULL;
}


/*
Hauptfunktion
*/
int main (void) {

  // Zahl von der Konsole einlesen und in number speichern
  char *n = (char*) malloc((MAXDIGITS+1)*sizeof(char));
  size_t maxDigits = MAXDIGITS;
  printf("Bitte gib eine zu pruefende Zahl ein: ");
  getline(&n, &maxDigits, stdin);
  int ret = mpz_init_set_str(number, n, 10);

  // Speicher wieder freigeben und Fehlerpruefung
  if (n != NULL) free(n);
  if (ret < 0) {
    printf("Fehler bei der Zuweisung der eingegebenen Zahl! Abbruch.\n");
    mpz_clear(number);
    return ret;
  }

  mpz_out_str(stdout, 10, number);
  printf(" ist... ");
  // 0 und 1 sind keine Primzahlen
  // 2 und 3 sind es hingegen
  if (mpz_cmp_si(number,0) == 0 || mpz_cmp_si(number,1) == 0) {
    printf("keine Primzahl.\n");
    mpz_clear(number);
    return EXIT_SUCCESS;
  } else if (mpz_cmp_si(number,2) == 0 || mpz_cmp_si(number,3) == 0) {
    printf("eine Primzahl.\n");
    mpz_clear(number);
    return EXIT_SUCCESS;
  }

  // Gerade Zahlen koennen sofort als nicht-prim erkannt werden
  mpz_t rest;
  mpz_init(rest);
  if (mpz_mod_ui(rest, number, 2) == 0) {
    printf("keine Primzahl.\n");
    mpz_clear(number);
    mpz_clear(rest);
    return EXIT_SUCCESS;
  } else mpz_clear(rest);

  // Grenzen fuer die Kandidaten moeglicher Teiler festlegen
  mpz_t bis;
  mpz_init(bis);
  // maximaler Teiler ist sqrt(number)
  mpz_root(bis, number, 2);
  mpz_add_ui(bis, bis, 1);

  // ist die Zahl kleiner als INT_MAX, brauchen wir nur einen Thread
  // -> Test ohnehin wenig aufwendig
  // -> auch fuer sehr triviale Festlegung der Suchgrenzen notwendig/hilfreich (s.u.)
  if (mpz_cmp_ui(number, INT_MAX) < 0) ANZTHREADS = 1;

  // ein paar Vorbereitungen
  pthread_t *threads = (pthread_t*) malloc(ANZTHREADS*sizeof(pthread_t));
  anf = (mpz_t*) malloc(ANZTHREADS*sizeof(mpz_t));
  ende = (mpz_t*) malloc(ANZTHREADS*sizeof(mpz_t));
  int i = 0;
  int *nr = (int*) malloc(ANZTHREADS*sizeof(int));;

  // Threads erzeugen
  // Achtung: so klappt es nur, wenn ANZTHREADS < sqrt(number)+3
  // Hinweis: Wenn number<INT_MAX, dann gilt eh ANZTHREADS==1 (s.o.)
  for (i = 0; i < ANZTHREADS; i++) {

    // Suchgrenzen fuer die Threads festlegen
    mpz_init(anf[i]);
    mpz_init(ende[i]);
    if (i == 0) {
      mpz_add_ui(anf[i], anf[i], 3);
    } else {
      mpz_cdiv_q_ui(anf[i], bis, ANZTHREADS);
      mpz_mul_ui(anf[i], anf[i], i);
    }
    mpz_cdiv_q_ui(ende[i], bis, ANZTHREADS);
    mpz_mul_ui(ende[i], ende[i], i+1);

    // Jeder Thread fuehrt "pruefeTeiler" aus.
    // Seine Ordnungsnummer wird ihm als Parameter uebergeben
    // -> dient zum Auslesen der Suchgrenzen des jeweiligen Threads
    nr[i]=i;
    pthread_create(&(threads[i]), NULL, pruefeTeiler, &nr[i]);
  }

  // Warten bis alle Threads zurueckgekehrt sind
  for (i = 0; i < ANZTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  // Ergebnis ausgeben
  if (found) {
    printf("keine Primzahl.\n");
  } else {
    printf("eine Primzahl.\n");
  }

  // aufraeumen
  mpz_clear(bis);
  mpz_clear(number);
  for (i = 0; i < ANZTHREADS; i++) {
    mpz_clear(anf[i]);
    mpz_clear(ende[i]);
  }
  if (threads != NULL) free(threads);
  if (anf != NULL) free(anf);
  if (ende != NULL) free(ende);
  if (nr != NULL) free(nr);

  // Ende
  return EXIT_SUCCESS;
}
