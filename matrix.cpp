#include "matrix.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>

matrix::matrix(flat a,float b, float c, float d){
    }

matrix operator +(matrix m1, matrix m2){
    if (s1.w=!s2.w || s1.h=!s2.h){
	throw(;
	return 1};
    r=s1.getreal()+s2.getreal();
    i=s1.getimag()+s2.getimag();
    complex temp(r,i);
    return temp;
    }

std::ostream& operator <<(std::ostream &so,matrix &m1){
    //so<<"wynik = "<<m1.real<<((m1.imag >= 0) ? "+" :"")<<s1.imag<<"i";
    return so;
}

