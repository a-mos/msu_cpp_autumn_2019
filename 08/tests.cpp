#include <iostream>
#include "Pool.h"

struct A {};

void foo(const A&) {}

int main() {

    ThreadPool pool(8);

    for (int i = 0; i < 10; ++i) {
        std::cout << pool.exec([i]() { return i; }).get() << std::endl;
    }

}
