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

// Access
double& Matrix::operator()(size_t i, size_t j) { return data(i, j); }
double Matrix::operator()(size_t i, size_t j) const { return data(i, j); }

// Ops
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

} // namespace tml
