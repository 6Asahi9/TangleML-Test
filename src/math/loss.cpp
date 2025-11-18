#include "math/loss.hpp"
#include <cmath>
#include <stdexcept>

namespace tml {
    // --------------------------- MSE ---------------------------
    // MSE =1/n ∑i ​( y_pred​(i)− y_true​(i))^2

    double MSELoss::forward(const Matrix& y_true, const Matrix& y_pred) const {
        if (y_true.rows() != y_pred.rows() || y_true.cols() != y_pred.cols())
            throw std::runtime_error("MSELoss: shape mismatch");

        Matrix diff = y_pred - y_true;
        double sum = diff.raw().array().square().sum();
        return sum / (y_true.rows() * y_true.cols());
    }

    Matrix MSELoss::backward(const Matrix& y_true, const Matrix& y_pred) const {
        return (y_pred - y_true) * (2.0 / (y_true.rows() * y_true.cols()));
    }

    // ---------------------- Cross Entropy ----------------------
    // CE = −∑​i log( y_pred​ (i, true_class))

    // y_true: Nx1 class indices
    // y_pred: NxC probabilities (softmax output)
    double CrossEntropyLoss::forward(const Matrix& y_true, const Matrix& y_pred) const {
        if (y_pred.cols() <= 1)
            throw std::runtime_error("CrossEntropyLoss: y_pred must be NxC");

        double loss = 0.0;
        for (size_t i = 0; i < y_true.rows(); i++) {
            int cls = (int)y_true.raw()(i, 0);
            loss += -std::log(y_pred.raw()(i, cls) + 1e-12);
        }
        return loss / y_true.rows();
    }

    Matrix CrossEntropyLoss::backward(const Matrix& y_true, const Matrix& y_pred) const {
        Matrix grad = y_pred; // copy

        for (size_t i = 0; i < y_true.rows(); i++) {
            int cls = (int)y_true.raw()(i, 0);
            grad.raw()(i, cls) -= 1.0;
        }

        return grad * (1.0 / y_true.rows());
    }

    // ------------------ Binary Cross Entropy ------------------
    // BCE = −(y_log(p) + (1 − y)log(1 − p))

    double BinaryCrossEntropyLoss::forward(const Matrix& y_true, const Matrix& y_pred) const {
        if (y_true.rows() != y_pred.rows() || y_true.cols() != y_pred.cols())
            throw std::runtime_error("BCELoss: shape mismatch");

        double s = 0.0;
        for (size_t i = 0; i < y_true.rows(); i++) {
            double t = y_true.raw()(i, 0);
            double p = y_pred.raw()(i, 0);
            s += -(t * std::log(p + 1e-12) + (1 - t) * std::log(1 - p + 1e-12));
        }

        return s / y_true.rows();
    }

    Matrix BinaryCrossEntropyLoss::backward(const Matrix& y_true, const Matrix& y_pred) const {
        Matrix grad(y_true.rows(), y_true.cols());
        for (size_t i = 0; i < y_true.rows(); i++) {
            double t = y_true.raw()(i, 0);
            double p = y_pred.raw()(i, 0);
            grad.raw()(i, 0) = -(t / (p + 1e-12) - (1 - t) / (1 - p + 1e-12));
        }
        return grad * (1.0 / y_true.rows());
    }

}
