#include <stdio.h>
#include "complex.h"

/*
 * "Funktionstest" - 2 komplexe Zahlen einlesen und alle implementierten Funktionen ausprobieren
 * Hinweis: Keine Fehlerbehandlungen der Eingaben in dieser Testroutine implementiert
 */
int main(void){
  complex x,y;
  double in;
  
  printf("x und y eingeben\n");
  printf("     Realteil von x: ");
  scanf("%lf",&in);
  x.re=in;
  printf("Imaginaerteil von x: ");
  scanf("%lf",&in);
  x.im=in;
  
  printf("     Realteil von y: ");
  scanf("%lf",&in);
  y.re=in;
  printf("Imaginaerteil von y: ");
  scanf("%lf",&in);
  y.im=in;

  printf("\nx = ");
  prettyprint(x);
  printf("\ny = ");
  prettyprint(y);
  printf("\n");

  printf("\nSumme:     x + y = ");
  prettyprint(cadd(x,y));

  printf("\nDifferenz: x - y = ");
  prettyprint(csub(x,y));

  printf("\nProdukt:   x * y = ");
  prettyprint(cmul(x,y));

  printf("\nQuotient:  x / y = ");
  prettyprint(cdiv(x,y));

  printf("\n");
  return 0;
}
