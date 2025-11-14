#include "math/matrix_ops.hpp"
#include <stdexcept>
namespace tml {
namespace ops {

    // Helper: ensure shape matches by ChatGPT
    static void check_same_shape(const Matrix& A, const Matrix& B) {
        if (A.rows() != B.rows() || A.cols() != B.cols())
            throw std::runtime_error("Matrix shapes do not match");
    }

    Matrix add(const Matrix& A, const Matrix& B) {
        check_same_shape(A, B);
        return Matrix(A.raw() + B.raw());
    }

    Matrix sub(const Matrix& A, const Matrix& B) {
        check_same_shape(A, B);
        return Matrix(A.raw() - B.raw());
    }

    Matrix mul_elementwise(const Matrix& A, const Matrix& B) {
        check_same_shape(A, B);
        return Matrix(A.raw().cwiseProduct(B.raw()));
    }

    Matrix div_elementwise(const Matrix& A, const Matrix& B) {
        check_same_shape(A, B);
        return Matrix(A.raw().cwiseQuotient(B.raw()));
    }

    Matrix matmul(const Matrix& A, const Matrix& B) {
        if (A.cols() != B.rows())
            throw std::runtime_error("Matrix multiplication dimension mismatch");

        return Matrix(A.raw() * B.raw());
    }

    Matrix transpose(const Matrix& A) {
        return Matrix(A.raw().transpose());
    }

    double determinant(const Matrix& A) {
        if (A.rows() != A.cols())
            throw std::runtime_error("Determinant requires a square matrix");

        return A.raw().determinant();
    }

    Matrix inverse(const Matrix& A) {
        if (A.rows() != A.cols())
            throw std::runtime_error("Inverse requires a square matrix");

        return Matrix(A.raw().inverse());
    }

    double frobenius_norm(const Matrix& A) {
        return A.raw().norm();
    }

} 
} 
