#pragma once
#include "core.hpp"
namespace tml {
namespace act {

    Matrix relu(const Matrix& x);
    Matrix leaky_relu(const Matrix& x, double alpha = 0.01);
    Matrix sigmoid(const Matrix& x);
    Matrix tanh(const Matrix& x);
    Matrix softmax(const Matrix& x);

    Matrix relu_deriv(const Matrix& x);
    Matrix leaky_relu_deriv(const Matrix& x, double alpha = 0.01);
    Matrix sigmoid_deriv(const Matrix& x);
    Matrix tanh_deriv(const Matrix& x);
    Matrix softmax_deriv(const Matrix& y); 
    
} 
} 
