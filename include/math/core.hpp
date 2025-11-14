#pragma once //a safety line “only include this file once, even if someone accidentally includes it multiple times.”
#include <Eigen/Dense>
#include <iostream>
#include <vector>

namespace tml {  // short for Tangle-ML , a namespace is like putting your code in its own box 
// so your class names don’t clash with others.
// you could have another library with a Matrix class — but because yours is in the tml namespace, it becomes:
// tml::Matrix
// instead of just Matrix.

class Matrix {
private:
    Eigen::MatrixXd data; //“Matrix of double precision (floating point) numbers”

public:
    // Constructors
    Matrix(); //Empty matrix, nothing inside
    Matrix(size_t rows, size_t cols); //Creates a zero matrix with those dimensions
    Matrix(const Eigen::MatrixXd& mat); //Wraps around an existing Eigen matrix
    //you’re passing a reference (&) to a matrix (to avoid copying big data)

    // Basic info
    size_t rows() const; //“size type”, an unsigned integer (it can’t be negative)
    size_t cols() const;
    // size_t rows();
    // you could accidentally change data inside the function.
    // adding const at the end locks it, making it “read-only.”

    // Access
    double& operator()(size_t i, size_t j);
    double operator()(size_t i, size_t j) const;

    // Operations
    Matrix transpose() const; //not a constructor 
    static Matrix identity(size_t n); //not an object 
    void print(const std::string& name = "") const; // print
    // wouldn't have needed it if Eigen wasn't in private

    // Conversion
    Eigen::MatrixXd& raw();
    const Eigen::MatrixXd& raw() const;
};

} // namespace tml
