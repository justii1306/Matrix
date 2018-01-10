#include <stdio.h>

class SizesDoNotMatch{};

class matrix{
private:
public:
    matrix(int,int);
    friend matrix operator +(matrix,matrix);
    friend matrix operator -(matrix,matrix);
    friend matrix operator *(matrix,matrix);
    matrix& operator +=(matrix&);
    matrix& operator -=(matrix&);
    matrix& operator *=(matrix&);
    matrix copy();
	void operator =(matrix);
	bool operator ==(matrix, matrix);
	void operator =();
	bool operator ==();
	friend ostream& operator <<(ostream &s, complex &b);
    };
