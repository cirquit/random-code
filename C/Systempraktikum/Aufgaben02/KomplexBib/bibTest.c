#include <ComplexMath.h>
#include <stdio.h>
#include <complex.h>


int main(int argc, char *argv[]){

    double negNum = -1;
    double complex negSqrt = csqrt(negNum);
    prettyPrint (negSqrt);
}

