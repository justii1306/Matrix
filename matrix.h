#include <stdio.h>

class matrix{
private:
public:
    matrix(float,float,float,float);
    friend matrix operator +(matrix,matrix);
    friend matrix operator -(matrix,matrix);
    friend matrix operator *(matrix,matrix);
    matrix operator +=(matrix);
    matrix operator -=(matrix);
    matrix operator *=(matrix);
    //matrix copy();
	void operator =();
	bool operator ==();
	friend std::ostream& operator <<(std::ostream &s, complex &b);
    };
