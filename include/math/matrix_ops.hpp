#pragma once
#include "math/core.hpp"

namespace tml {
namespace ops {

    // Basic arithmetic
    Matrix add(const Matrix& A, const Matrix& B);
    Matrix sub(const Matrix& A, const Matrix& B);
    Matrix mul_elementwise(const Matrix& A, const Matrix& B);
    Matrix div_elementwise(const Matrix& A, const Matrix& B);

    // Matrix multiplication
    Matrix matmul(const Matrix& A, const Matrix& B);

    Matrix transpose(const Matrix& A); //ops::transpose() is duplicated work.
    // Why I initially added ops::transpose()
    // Some ML libraries separate:
    // core = the data structure (Matrix class)
    // ops = functional API (free-function operations)
    // Example:
    // PyTorch has both tensor.t() and torch.transpose(tensor).

    double determinant(const Matrix& A);
    Matrix inverse(const Matrix& A);
    double frobenius_norm(const Matrix& A);

} 
} 
