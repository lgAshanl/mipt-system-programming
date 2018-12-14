#include <iostream>

#include "Computer.h"

int main() {
    init_asm();
    std::cout << "start\n";
    parse_program("./program.asm");
    std::cout << "end\n";
    return 0;
}