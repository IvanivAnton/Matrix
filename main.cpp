#include <iostream>
#include "Matrix.hxx"
using namespace std;

int main() {
    Matrix matrix1(3,3,"x");
    matrix1.printMt();
    matrix1.determinant();
    matrix1.transpose();
    matrix1.printMt();
    matrix1.determinant();
    return 0;
}