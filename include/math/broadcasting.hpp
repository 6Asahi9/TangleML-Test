#pragma once
#include "core.hpp"

namespace tml {
namespace ops {

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

} // namespace ops
} // namespace tml
