#include <math.h>
#include <fstream>
#include "Matrix.h"

void matrix::check(unsigned int i){
	if(block->rows<i)
		throw IndexOutOfRange();
}

matrix::matrix(std::fstream& fs){
	block = new rcmatrix(fs);
}

matrix::matrix(const matrix& cm){
	cm.block->n++;
	block = cm.block;
}

matrix::~matrix(){
	if(--block->n==0)
		delete block;
}

matrix::matrix(){
	block = new rcmatrix();
}

matrix::matrix(unsigned int nrows, unsigned int ncols, double var){
    block = new rcmatrix(nrows,ncols,var);
}

matrix::matrix(unsigned int nrows, unsigned int ncols, double var1, double var2){
	block = new rcmatrix(nrows,ncols,var1,var2);
}

matrix& matrix::operator = (const matrix& asOp){
	asOp.block->n++;
	if(--block->n == 0)
		delete block;

	block=asOp.block;
	return *this;
}

matrix & matrix::operator=(double** co){
	if(block->n==1){
	block->assign(co);
	}
	else{
		rcmatrix* t= new rcmatrix(1,1,co);
	this->block->n--;
	this->block = t;
	}
	return *this;
}

std::ostream & operator << (std::ostream & s, const matrix & matrix){
	//std::cout << "matrix.cols=" << matrix.block->cols <<std::endl;
	s << "[";
	for(unsigned int i=0;i<matrix.block->rows;i++){
		for(unsigned int j=0;j<matrix.block->cols;j++){
			s << matrix.block->data[i][j];
			if(((j+1) % matrix.block->cols) == 0 && j!=0 && i!=matrix.block->rows-1)
				s << "\n ";
			if(!(i==matrix.block->rows-1 && j==matrix.block->cols-1) && j!=matrix.block->cols-1)
				s << ", ";
		}
	}
	s << "]";
	return s;
}

matrix operator * (const matrix& m1, const matrix& m2){
	if(m1.block->cols != m2.block->rows)
		throw WrongDim();

	matrix newMatrix(m1.block->rows, m2.block->cols,0.0);

	for(unsigned int i=0;i<newMatrix.block->rows;i++)
		for(unsigned int j=0;j<newMatrix.block->cols;j++){
			double var=0.0;
			for(unsigned int lol=0;lol<m1.block->cols;lol++)
				var += m1.block->data[i][lol]*m2.block->data[lol][j];
			newMatrix.block->data[i][j] = var;
		}
	return newMatrix;
}

double* matrix::read(unsigned int i) const{
	try{
	return block->data[i];
	}
	catch(...){
	throw IndexOutOfRange();
	}
}

void matrix::write(unsigned int i, double* c){
	block = block->detach();
	try{
	block->data[i] = c;
	}
	catch(...){
	throw IndexOutOfRange();
	}
}

matrix::Cref matrix::operator[](unsigned int i){
  std::cout << "Cref rcstring::operator[](unsigned int i) CALLED"<<std::endl;
  check(i);
  return Cref(*this,i);
}

std::ostream& operator<<(std::ostream& o, const matrix::Cref& s1){
std::cout << "operator<<(std::ostream& o, const matrix::Cref& s1)\\n"<<std::endl;
	o << s1.s.block->data[s1.i][s1.i];
	return o;
}

matrix operator +(const matrix& m1, const matrix& m2){
    if((m1.block->rows!=m2.block->rows)&&(m1.block->cols!=m2.block->cols))
		throw WrongDim();

    matrix result(m1.block->rows,m1.block->cols,0.0);

	for(int i=0; i<result.block->rows; i++){
		for(int j=0; j<result.block->cols;j++){
			result.block->data[i][j]=m1.block->data[i][j]+m2.block->data[i][j];}}

    return result;}

matrix operator -(const matrix& m1, const matrix& m2){
    if((m1.block->rows!=m2.block->rows)&&(m1.block->cols!=m2.block->cols))
		throw WrongDim();

    matrix result(m1.block->rows,m1.block->cols,0.0);

	for(int i=0; i<result.block->rows; i++){
		for(int j=0; j<result.block->cols; j++){
			result.block->data[i][j]=m1.block->data[i][j]-m2.block->data[i][j];}}

    return result;}
