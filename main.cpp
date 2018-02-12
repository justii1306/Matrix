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
    std::cout <<"+: " << std::endl << c << std::endl;
    std::cout <<"-: " << std::endl << d << std::endl;
    matrix e(2,2,1);
    std::cout <<"e: " << std::endl << e << std::endl;
    e+=a;
    std::cout <<"+=: " << std::endl << e << std::endl;
    matrix f(2,2,1);
    std::cout <<"f: " << std::endl << f << std::endl;
    f-=a;
    std::cout <<"-=: " << std::endl << f << std::endl;
    matrix g=a*b;
    std::cout <<"*: " << std::endl << g << std::endl;
    matrix h(2,2,2);
    std::cout <<"h: " << std::endl << h << std::endl;
    h*=b;
    std::cout <<"*=: " << std::endl << h << std::endl;
    matrix i=a;
    std::cout <<"=: " << std::endl << i << std::endl;
    std::cout <<"i==a: " << (i==a) << std::endl;
    std::cout <<"i==b: " << (i==b) << std::endl;
    matrix j(a);
    std::cout <<"j: " << std::endl << j << std::endl;

    std::fstream fs;
    fs.open ("testt.txt", std::fstream::in);
    matrix file(fs);
    std::cout << "file:" << std::endl<< file << std::endl;
    fs.close();

    matrix k(5,5,8);
    std::cout << "k:" << std::endl<< k << std::endl;
    double zm = k(1, 4);
    std::cout << "k(1, 4): " << zm << std::endl;
    k(1, 4) = 7;
    std::cout << "k(1, 4) = 7" << std::endl;
    std::cout << "k:" << std::endl<< k << std::endl;

    return 0;

}
