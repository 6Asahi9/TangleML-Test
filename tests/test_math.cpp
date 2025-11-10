#include <iostream>
#include <vector>
#include "../include/math/core.hpp" 

int main() {
    std::cout << "[WORKING] Running Tangle-ML Math Test!" << std::endl;

    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {4, 5, 6};
    std::vector<int> c(a.size());

    for (size_t i = 0; i < a.size(); ++i) {
        c[i] = a[i] + b[i];
    }

    std::cout << "[RESULT] Vector addition result: ";
    for (int val : c) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "[OK] Math test finished successfully!" << std::endl;
    return 0;
}
