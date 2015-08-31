/*
 * Typ definieren, der complex heisst und zwei double-Werte beinhaltet.
 * z.B. Variable
 * complex c;
 * c.re=1.2;
 * c.im=2.4;
 */
typedef struct {
  double re;
  double im;
} complex;

// Addition komplexer Zahlen: x + y
// Rueckgabe: Ergebnis im Typ "complex"
complex cadd (complex x, complex y);

// Subtraktion komplexer Zahlen: x - y
// Rueckgabe: Ergebnis im Typ "complex"
complex csub (complex x, complex y);

// Multiplikation komplexer Zahlen: x * y
// Rueckgabe: Ergebnis im Typ "complex"
complex cmul (complex x, complex y);

// Division komplexer Zahlen: x / y
// Rueckgabe: Ergebnis im Typ "complex"
complex cdiv (complex x, complex y);

// Menschenlesbare Ausgabe einer komplexen Zahl
void prettyprint(complex z);
