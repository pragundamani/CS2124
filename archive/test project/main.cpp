#include <iostream>
#include "math_ops.h"
#include "string_ops.h"

int main() {
    std::cout << "Multi-file compilation test\n";
    std::cout << "==========================\n\n";
    
    std::cout << "Math operations:\n";
    std::cout << "5 + 3 = " << add(5, 3) << "\n";
    std::cout << "10 * 4 = " << multiply(10, 4) << "\n\n";
    
    std::cout << "String operations:\n";
    std::cout << "Uppercase: " << toUpper("hello world") << "\n";
    std::cout << "Reverse: " << reverse("C++ rocks") << "\n";
    
    return 0;
}
