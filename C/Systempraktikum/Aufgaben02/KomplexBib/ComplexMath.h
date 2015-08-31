#ifndef ComplexMath
#define ComplexMath
#include <complex.h>

/*
 * Defining * adding         z = (a + bi) + (c + di) = (a + c) + (b + d)i
            * subtraction    z = (a + bi) − (c + di) = (a − c) + (b − d)i
            * multiplying    z = (a + bi)(c + di)    = (ac − bd) + (ad + bc)i
            * dividing       z = (a + bi) / (c + di)   = ((ac + bd) / (c^2 + d^2)) + ((bc - ad) / (c^2 + d^2)) * i
   for complex numbers  
 */

double complex addComplex (double complex x, double complex y);

double complex subtractComplex (double complex x, double complex y);

double complex multiplyComplex (double complex x, double complex y);

double complex divideComplex (double complex x, double complex y);
    // checking if the denominator is zero 

void prettyPrint (double complex x);

#endif 