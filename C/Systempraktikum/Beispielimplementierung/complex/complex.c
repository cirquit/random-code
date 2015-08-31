#include "complex.h"
#include <stdio.h>

// Addieren von zwei komplexen Zahlen
complex cadd (complex x, complex y) {
  complex z;
  z.re = x.re + y.re;
  z.im = x.im + y.im;
  return z;
}

// Subtrahieren von zwei komplexen Zahlen
complex csub (complex x, complex y) {
  complex z;
  z.re = x.re - y.re;
  z.im = x.im - y.im;
  return z;
}

// Multiplizieren von zwei komplexen Zahlen
complex cmul (complex x, complex y) {
  complex z;
  z.re = x.re * y.re - x.im * y.im;
  z.im = x.re * y.im + x.im * y.re;
  return z;
}

// Dividieren von zwei komplexen Zahlen
complex cdiv (complex x, complex y) {
  complex z;
  if (y.re == 0 && y.im == 0) {
    printf("Division durch 0!");
    z.re = 0.0;
    z.im = 0.0;
  } else {
    z.re = (x.re * y.re + x.im * y.im) / (y.re * y.re + y.im * y.im);
    z.im = (x.im * y.re - x.re * y.im) / (y.re * y.re + y.im * y.im);
  }
  return z;
}

// Komplexe Zahl schoen formatiert ausgeben
void prettyprint (complex z) {
  printf("(%.3f + %.3fi)", z.re, z.im);
}
