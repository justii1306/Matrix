#include <math.h>
#include <fstream>
#include "Matrix.h"

int main(){
    matrix a;
    matrix b(5, 5, 1);
    matrix c(5, 5, 1, 2);
    matrix d(c);
    std::cout<<a<<std::endl;
    std::cout<<b<<std::endl;
    std::cout<<c<<std::endl;
    std::cout<<d<<std::endl;
	int x1;
	x1 = d[2][1];
	std::cout<<"x1: "<<x1<<std::endl;
	std::cout<<d<<std::endl;
	std::cout<<"-------------------------------------------"<<std::endl;
	d[2][1] = 8;
	std::cout<<d[2][1]<<std::endl;
	std::cout<<d<<std::endl;
	matrix a(2,2,1);
matrix b(2,2,2);
matrix c = a + b;
std::cout << a << std::endl;
std::cout << b << std::endl;
std::cout << c << std::endl;
    return 0;

}
