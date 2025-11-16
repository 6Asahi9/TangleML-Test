#include "math/core.hpp"

namespace tml {

// Constructors
Matrix::Matrix() : data(Eigen::MatrixXd()) {}

Matrix::Matrix(size_t rows, size_t cols)
    : data(Eigen::MatrixXd::Zero(rows, cols)) {}

Matrix::Matrix(const Eigen::MatrixXd& mat) : data(mat) {}

// Info
size_t Matrix::rows() const { return data.rows(); }
size_t Matrix::cols() const { return data.cols(); }

std::pair<size_t, size_t> Matrix::shape() const {
    return { rows(), cols() };
}

// Access
double& Matrix::operator()(size_t i, size_t j) { return data(i, j); }
double Matrix::operator()(size_t i, size_t j) const { return data(i, j); }

// Operations
Matrix Matrix::transpose() const {
    return Matrix(data.transpose());
}

Matrix Matrix::identity(size_t n) {
    return Matrix(Eigen::MatrixXd::Identity(n, n));
}

void Matrix::print(const std::string& name) const {
    if (!name.empty())
        std::cout << name << ":\n";
    std::cout << data << "\n";
}

// Conversion
Eigen::MatrixXd& Matrix::raw() { return data; }
const Eigen::MatrixXd& Matrix::raw() const { return data; }

// Arithmetic
Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(rows(), cols());
    result.raw() = data - other.data;
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(rows(), cols());
    result.raw() = data + other.data;
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows(), cols());
    result.raw() = data * scalar;
    return result;
}

Matrix operator*(double scalar, const Matrix& m) {
    Matrix result(m.rows(), m.cols());
    result.raw() = scalar * m.data;
    return result;
}

// Matrix multiplication
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols() != other.rows()) {
        throw std::runtime_error("Matrix dimension mismatch for multiplication.");
    }
    return Matrix(data * other.data);
}

} // namespace tml
