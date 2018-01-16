#include <math.h>
#include <fstream>
#include "Matrix.h"

void matrix::check(unsigned int i){
	if(block->rows<i)
		throw IndexOutOfRange();}

matrix::matrix(std::fstream& fs){
	block = new rcmatrix(fs);}

matrix::matrix(const matrix& cm){
	cm.block->n++;
	block = cm.block;}

matrix::~matrix(){
	if(--block->n==0)
		delete block;}

matrix::matrix(){
	block = new rcmatrix();}

matrix::matrix(unsigned int nrows, unsigned int ncols, double var){
    block = new rcmatrix(nrows,ncols,var);}

matrix& matrix::operator = (const matrix& asOp){
	asOp.block->n++;
	if(--block->n == 0)
		delete block;

	block=asOp.block;
	return *this;}

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

double matrix::read(unsigned int i, unsigned int j) const{
    std::cout << "read" << std::endl;
	try{
	return block->data[i][j];
	}
	catch(...){
	throw IndexOutOfRange();
	}
}

void matrix::write(unsigned int i, unsigned j, double c){
    std::cout << "write" << std::endl;
	block = block->detach();
	try{
	block->data[i][j] = c;
	}
	catch(...){
	throw IndexOutOfRange();
	}
}

matrix::Cref matrix::operator()(unsigned int i, unsigned int j){
  std::cout << "Cref rcstring::operator[](unsigned int i) CALLED"<<std::endl;
  check(i);
  check(j);
  return Cref(*this,i,j);
}

std::ostream& operator<<(std::ostream& o, const matrix::Cref& s1){
std::cout << "operator<<(std::ostream& o, const matrix::Cref& s1)"<<std::endl;
	o << s1.s.block->data[s1.i][s1.j];
	return o;}


matrix operator +(const matrix& m1, const matrix& m2){
    if((m1.block->rows!=m2.block->rows)||(m1.block->cols!=m2.block->cols))
		throw WrongDim();

    matrix result(m1.block->rows,m1.block->cols,0.0);

	for(int i=0; i<result.block->rows; i++){
		for(int j=0; j<result.block->cols;j++){
			result.block->data[i][j]=m1.block->data[i][j]+m2.block->data[i][j];}}

    return result;}


matrix operator -(const matrix& m1, const matrix& m2){
    if((m1.block->rows!=m2.block->rows)||(m1.block->cols!=m2.block->cols))
		throw WrongDim();

    matrix result(m1.block->rows,m1.block->cols,0.0);

	for(int i=0; i<result.block->rows; i++){
		for(int j=0; j<result.block->cols; j++){
			result.block->data[i][j]=m1.block->data[i][j]-m2.block->data[i][j];}}

    return result;}


matrix& matrix::operator+=(matrix& m2){
    if((this->block->rows!=m2.block->rows)||(this->block->cols!=m2.block->cols))
		throw WrongDim();

    this->block = this->block->detach();

    for(int i=0; i<this->block->rows; i++){
		for(int j=0; j<this->block->cols; j++){
			this->block->data[i][j]=this->block->data[i][j]+m2.block->data[i][j];}}}


matrix& matrix::operator-=(matrix& m2){
    if((this->block->rows!=m2.block->rows)||(this->block->cols!=m2.block->cols))
		throw WrongDim();

    this->block = this->block->detach();

    for(int i=0; i<this->block->rows; i++){
		for(int j=0; j<this->block->cols; j++){
			this->block->data[i][j]=this->block->data[i][j]-m2.block->data[i][j];}}}


matrix operator *(const matrix& m1, const matrix& m2){
	if((m1.block->rows!=m2.block->rows)||(m1.block->cols!=m2.block->cols))
		throw WrongDim();

	matrix result(m1.block->rows, m2.block->cols,0.0);

	for(int i=0;i<result.block->rows;i++)
		for(int j=0;j<result.block->cols;j++){
			double var=0.0;
			for(int l=0;l<m1.block->cols;l++)
				var += m1.block->data[i][l]*m2.block->data[l][j];
			result.block->data[i][j] = var;}

	return result;}

matrix& matrix:: operator *=(const matrix& m2){
	if((this->block->rows!=m2.block->rows)||(this->block->cols!=m2.block->cols))
		throw WrongDim();

	this->block=this->block->detach();

	matrix result(this->block->rows, this->block->cols,0.0);

	for(int i=0;i<result.block->rows;i++)
		for(int j=0;j<result.block->cols;j++){
			double var=0.0;
			for(int l=0;l<this->block->cols;l++)
				var += this->block->data[i][l]*m2.block->data[l][j];
			result.block->data[i][j] = var;}

    for(int i=0;i<result.block->rows;i++){
        for(int j=0;j<result.block->cols;j++){
            this->block->data[i][j]=result.block->data[i][j];}}

	return *this;}

bool matrix:: operator==(const matrix& m2){
     if((this->block->rows!=m2.block->rows)||(this->block->cols!=m2.block->cols))
		return false;

    for(int i=0;i<this->block->rows;i++){
        for(int j=0;j<this->block->cols;j++){
            if(this->block->data[i][j]!=m2.block->data[i][j])
                return false;}}

    return true;}

