#include "assert.h"
#include <iostream>
#include "DieHardStack.h"

int main() {
    DieHardStack<int> a;
    a.push(3);
    assert(a.isValid());
    assert(a.pop() == 3);
    assert(a.isValid());
    a.print();
    return 0;
}