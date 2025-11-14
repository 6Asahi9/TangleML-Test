#include "include/math/core.hpp"
#include "math/matrix_ops.hpp"
using namespace tml;

int main() {
    Matrix A(2, 2);
    A(0, 0) = 1.0; A(0, 1) = 2.0;
    A(1, 0) = 3.0; A(1, 1) = 4.0;

    A.print("A");
    Matrix B = A.transpose();
    B.print("A Transposed");

    Matrix I = Matrix::identity(3);
    I.print("Identity");

    return 0;
}
