#include "math/activations.hpp"
#include <cmath>
namespace tml {
namespace act {

    // ReLU
    Matrix relu(const Matrix& x) {
        return Matrix(x.raw().array().max(0.0));
    }

    Matrix relu_deriv(const Matrix& x) {
        return Matrix((x.raw().array() > 0.0).cast<double>());
    }

    // Leaky ReLU
    Matrix leaky_relu(const Matrix& x, double alpha) {
        return Matrix(x.raw().unaryExpr([alpha](double v) {
            return v > 0 ? v : alpha * v;
        }));
    }

    Matrix leaky_relu_deriv(const Matrix& x, double alpha) {
        return Matrix(x.raw().unaryExpr([alpha](double v) {
            return v > 0 ? 1.0 : alpha;
        }));
    }

    // Sigmoid
    Matrix sigmoid(const Matrix& x) {
        return Matrix((1.0 / (1.0 + (-x.raw().array()).exp())).matrix());
    }

    Matrix sigmoid_deriv(const Matrix& x) {
        Eigen::ArrayXXd s = 1.0 / (1.0 + (-x.raw().array()).exp());
        return Matrix((s * (1.0 - s)).matrix());
    }

    // Tanh
    Matrix tanh(const Matrix& x) {
        return Matrix(x.raw().array().tanh());
    }

    Matrix tanh_deriv(const Matrix& x) {
        auto t = x.raw().array().tanh();
        return Matrix((1.0 - t * t).matrix());
    }

    // Softmax (row-wise)
    Matrix softmax(const Matrix& x) {
        Eigen::MatrixXd y(x.rows(), x.cols());

        for (int i = 0; i < x.rows(); ++i) {
            double max_val = x.raw().row(i).maxCoeff();
            Eigen::ArrayXd exps = (x.raw().row(i).array() - max_val).exp();
            double sum = exps.sum();
            y.row(i) = (exps / sum).matrix();
        }

        return Matrix(y);
    }

    // Softmax derivative: y is already softmax(x)
    Matrix softmax_deriv(const Matrix& y) {
        // derivative: y * (1 - y), elementwise (for cross-entropy case)
        return Matrix((y.raw().array() * (1.0 - y.raw().array())).matrix());
    }

} 
} 
