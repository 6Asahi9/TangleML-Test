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
    //Gives you direct access to the underlying Eigen object.
    // Aggressive: Use this only if you know what you’re doing. Otherwise, your Matrix class is useless if you just go wild with Eigen.

    // Arithmetic
    Matrix operator-(const Matrix& other) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    friend Matrix operator*(double scalar, const Matrix& m);
    //     Overloads +, -, *.
    // Makes your Matrix behave like normal math.
    // friend → allows function outside the class to access private stuff.
    // Aggressive: Don’t touch friend unless you want to feel both powerful and guilty.

    std::pair<size_t, size_t> shape() const;
    //Returns (rows, cols) as a pair.
    // Aggressive: Stop guessing matrix dimensions. This tells you straight up.

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const;
    // Matrix multiplication operator overload.
    // Aggressive: If you confuse element-wise * with matrix multiplication, I will come over and slap your CPU.

};

} // namespace tml
