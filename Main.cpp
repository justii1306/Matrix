#include <math.h>
#include <fstream>
#include "Matrix.h"

int main(){
	matrix a(2,2,1);
    matrix b(2,2,2);
    matrix c = a + b;
    matrix d = a - b;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    matrix z(a);
    a += b;
    std::cout << a << std::endl;
    std::cout << z << std::endl;
    return 0;

}
