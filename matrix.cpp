#include "matrix.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;

matrix operator +(matrix m1, matrix m2){
	int j,i;
    matrix mw(m1.rows,m1.columns);
    if(m1.rows!=m2.rows || m1.columns!=m2.columns)
	throw SizesDoNotMatch();   
    for(i=0;i<m.rows;i++){
		for(j=o;j<r1.columns;j++)
			mw[i][j]=m1[i][j]+m2[i][j];
	}
	return mw;}

matrix operator -(matrix m1, matrix m2){
    if(m1.rows!=m2.rows || m1.columns!=m2.columns)
	throw SizesDoNotMatch();  
		throw SizesDoNotMatch();   
    for(i=0;i<m.rows;i++){
		for(j=o;j<r1.columns;j++)
			mw[i][j]=m1[i][j]-m2[i][j]; 
    
    }

matrix operator *(matrix m1, matrix m2){
    if(m1.rows!=m2.columns || m1.columns!=m2.rows)
	throw SizesDoNotMatch();   
    
    }

matrix operator +=(matrix m2){
    if(this->rows!=m2.rows || this->columns!=m2.columns)
	throw SizesDoNotMatch();   
    
    }

matrix operator -=(matrix m2){
    if(this->rows!=m2.rows || mthis->columns!=m2.columns)
	throw SizesDoNotMatch();   
    
    }

matrix operator *=(matrix m2){
    if(this->rows!=m2.columns || this->columns!=m2.rows)
	throw SizesDoNotMatch();   
    
    }
