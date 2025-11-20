#pragma once
#include "core.hpp"

namespace tml {
namespace ops {

// But broadcasting is NOT for dot product.
// Broadcasting is for element-wise operations, not matrix multiplication.

// Dot product rules:
// If shapes don’t match → ❌ ILLEGAL
// No stretching allowed
// This is pure linear algebra

// Broadcasting rules:
// Used in machine learning, not classical math
// It defines how small arrays expand to match big arrays

// Lets you write simple code like:
// output = weights * input + bias

// Even if bias is a vector and weights * input is a big matrix

// Why ML needs broadcasting (plain truth)
// When doing neural networks:
// 1. You get something like:
// Z = W * X   → gives shape (m, n)
// Z + b (bias) before activation

class Broadcasting {
public:
    // Expand a matrix to a target shape
    static Matrix broadcast_to(const Matrix& mat, size_t target_rows, size_t target_cols);

    // Vector broadcast ops (row or column vector)
    static Matrix add_vector(const Matrix& A, const Matrix& v);
    static Matrix sub_vector(const Matrix& A, const Matrix& v);
    static Matrix mul_vector(const Matrix& A, const Matrix& v);
    static Matrix div_vector(const Matrix& A, const Matrix& v);

    // Scalar broadcast ops
    static Matrix add_scalar(const Matrix& A, double s);
    static Matrix sub_scalar(const Matrix& A, double s);
    static Matrix mul_scalar(const Matrix& A, double s);
    static Matrix div_scalar(const Matrix& A, double s);

    // Matrix + Matrix with broadcasting
    static Matrix add(const Matrix& A, const Matrix& B);
    static Matrix subtract(const Matrix& A, const Matrix& B);
    static Matrix multiply(const Matrix& A, const Matrix& B);
    static Matrix divide(const Matrix& A, const Matrix& B);
};
// ➤ Scalar → applies to every element
// ➤ Row vector → repeats downward
// ➤ Column vector → repeats sideways
// ➤ Small matrix → expanded to match bigger one (if shape compatible)

} // namespace ops
} // namespace tml
