#include "math/broadcasting.hpp"
#include <stdexcept>

namespace tml {
namespace ops {

static bool is_row_vector(const Matrix& v) {
    return v.rows() == 1 && v.cols() >= 1;
}

static bool is_col_vector(const Matrix& v) {
    return v.cols() == 1 && v.rows() >= 1;
}

Matrix Broadcasting::broadcast_to(const Matrix& mat, size_t target_rows, size_t target_cols) {
    if (mat.rows() == target_rows && mat.cols() == target_cols)
        return mat;

    Matrix out(target_rows, target_cols);

    if (mat.rows() == 1 && mat.cols() == 1) {
        out.raw() = Eigen::MatrixXd::Constant(target_rows, target_cols, mat.raw()(0,0));
        return out;
    }

    if (is_row_vector(mat) && mat.cols() == target_cols) {
        out.raw().rowwise() = mat.raw().row(0);
        return out;
    }

    if (is_col_vector(mat) && mat.rows() == target_rows) {
        out.raw().colwise() = mat.raw().col(0);
        return out;
    }

    throw std::runtime_error("Invalid broadcasting dimensions");
}

Matrix Broadcasting::add(const Matrix& A, const Matrix& B) {
    auto B2 = broadcast_to(B, A.rows(), A.cols());
    return Matrix(A.raw() + B2.raw());
}

Matrix Broadcasting::subtract(const Matrix& A, const Matrix& B) {
    auto B2 = broadcast_to(B, A.rows(), A.cols());
    return Matrix(A.raw() - B2.raw());
}

Matrix Broadcasting::multiply(const Matrix& A, const Matrix& B) {
    auto B2 = broadcast_to(B, A.rows(), A.cols());
    return Matrix(A.raw().array() * B2.raw().array());
}

Matrix Broadcasting::divide(const Matrix& A, const Matrix& B) {
    auto B2 = broadcast_to(B, A.rows(), A.cols());
    return Matrix(A.raw().array() / B2.raw().array());
}

} 
} 
