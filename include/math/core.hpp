#pragma once
#include <Eigen/Dense>
#include <iostream>
#include <vector>

namespace tml {  // short for Tangle-ML

class Matrix {
private:
    Eigen::MatrixXd data;

public:
    // Constructors
    Matrix();
    Matrix(size_t rows, size_t cols);
    Matrix(const Eigen::MatrixXd& mat);

    // Basic info
    size_t rows() const;
    size_t cols() const;

    // Access
    double& operator()(size_t i, size_t j);
    double operator()(size_t i, size_t j) const;

    // Operations
    Matrix transpose() const;
    static Matrix identity(size_t n);
    void print(const std::string& name = "") const;

    // Conversion
    Eigen::MatrixXd& raw();
    const Eigen::MatrixXd& raw() const;
};

} // namespace tml
