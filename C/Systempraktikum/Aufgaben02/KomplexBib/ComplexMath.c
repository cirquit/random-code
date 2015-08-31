#include "ComplexMath.h"
#include <stdio.h>

/*
 * Defining * adding         z = (a + bi) + (c + di) = (a + c) + (b + d)i
            * subtraction    z = (a + bi) − (c + di) = (a − c) + (b − d)i
            * multiplying    z = (a + bi)(c + di)    = (ac − bd) + (ad + bc)i
            * dividing       z = (a + bi) / (c + di)   = ((ac + bd) / (c^2 + d^2)) + ((bc - ad) / (c^2 + d^2)) * i
   for complex numbers  
 */

double complex addComplex (double complex x, double complex y){

  return x + y;
}

double complex subtractComplex (double complex x, double complex y){
 
  return x - y;
}

double complex multiplyComplex (double complex x, double complex y){

  return x * y;
}

double complex divideComplex (double complex x, double complex y){
 
  float yr=  creal(y);  float yi = cimag(y);
  if (yr == 0 && yi == 0) {printf ("Division by zero, returning x"); return x;}
   else {return x / y;}
}
    // checking if the denominator is zero 

void prettyPrint (double complex x){
  printf("The complex number is = %0.2f + %0.2fi\n", creal(x), cimag(x));
}
