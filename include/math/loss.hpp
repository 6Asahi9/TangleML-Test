#pragma once
#include "core.hpp"
namespace tml {

    class Loss {
    public:
        virtual ~Loss() = default;
    // virtual = tells C++: “Derived classes might override this function”
    // ~Loss() = destructor → cleans up memory when object dies
    // = default = use the compiler-generated destructor (no fancy stuff)
    // Aggressive: This is just a cleanup placeholder, so your objects don’t leak memory.

        // Forward pass
        virtual double forward(const Matrix& y_true, const Matrix& y_pred) const = 0;

        // Backward pass (dLoss/dPred)
        virtual Matrix backward(const Matrix& y_true, const Matrix& y_pred) const = 0;
    // virtual + = 0 = pure virtual function
    // Pure virtual = “I don’t do anything here, but any class that inherits Loss must implement this”
    // const = promise not to change the object itself
    // Matrix& y_true = reference, avoid copying large Matrix objects
    // double forward(...) = returns the loss value
    // Matrix backward(...) = returns gradient with respect to predictions
    // Aggressive: Think of Loss as a contract. It says: “Any Loss class must have forward() and backward() methods. No excuses.
    };

    class MSELoss : public Loss {
    public:
        double forward(const Matrix& y_true, const Matrix& y_pred) const override;
        Matrix backward(const Matrix& y_true, const Matrix& y_pred) const override;
    };
    // : public Loss → MSELoss inherits Loss (is-a relationship)
    // override → tells compiler: “I am intentionally overriding a virtual function from the base class”
    // Aggressive: MSELoss is a real worker, it will actually compute the mean squared error. The base Loss just talked big.

    class CrossEntropyLoss : public Loss {
    public:
        // y_true = class indices (one per row)
        double forward(const Matrix& y_true, const Matrix& y_pred) const override;
        Matrix backward(const Matrix& y_true, const Matrix& y_pred) const override;
    };
    // 2b: CrossEntropyLoss & BinaryCrossEntropyLoss
    // Same pattern: inherit Loss, override forward and backward
    // Comment about y_true = class indices → in cross-entropy, labels are integers (not one-hot)
    class BinaryCrossEntropyLoss : public Loss {
    public:
        double forward(const Matrix& y_true, const Matrix& y_pred) const override;
        Matrix backward(const Matrix& y_true, const Matrix& y_pred) const override;
    };

}
