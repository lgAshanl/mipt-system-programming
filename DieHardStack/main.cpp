#include <iostream>
#include "DieHardStack.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    DieHardStack<int> a;
    a.push(3);
    std::cout << a.isValid() << "\n";
    std::cout << a.pop() << "\n";
    std::cout << a.isValid() << "\n";
    return 0;
}