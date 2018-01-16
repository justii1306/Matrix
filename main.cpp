#include <math.h>
#include <fstream>
#include "Matrix.h"

int main(){
	matrix a(2,2,1);
    matrix b(2,2,2);
    matrix c = a + b;
    matrix d = a - b;
    std::cout <<"a: " << std::endl << a << std::endl;
    std::cout <<"b: " << std::endl << b << std::endl;
    std::cout <<"c: " << std::endl << c << std::endl;
    std::cout <<"d: " << std::endl << d << std::endl;
    matrix e=a*b;
    matrix f=a;
    std::cout <<"f==a: " << std::endl << (f==a) << std::endl;
    std::cout <<"f==b: " << std::endl << (f==b) << std::endl;
    a*=b;
    std::cout <<"eaa: " << std::endl << a << std::endl;
    matrix z(a);
    a += b;
    std::cout <<"a: " << std::endl << a << std::endl;
    std::cout <<"z: " << std::endl << z << std::endl;

    std::fstream fs;
    fs.open ("test.txt", std::fstream::in);
    matrix file(fs);
    std::cout << "file:" << std::endl<< file << std::endl;
    fs.close();

    matrix mariusz(9,9,7);
    std::cout << "mariusz:" << std::endl<< mariusz << std::endl;
    double d_mariusz = mariusz(2, 3);
    std::cout << "mariusz(2, 3): " << d_mariusz << std::endl;
    mariusz(2, 3) = 4;
    std::cout << "mariusz(2, 3) = 4" << std::endl;
    std::cout << "mariusz:" << std::endl<< mariusz << std::endl;

    return 0;

}
