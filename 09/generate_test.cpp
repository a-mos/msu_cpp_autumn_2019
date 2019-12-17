#include <iostream>
#include <fstream>

//argv[1] - output name, argv[2] - output size
int main(const int argc, const char **argv) {
    std::ofstream f(argv[1], std::ios::binary);
    for (size_t i = 0; i < atoi(argv[2]) * 1024 * 1024; ++i) {
        uint64_t r = rand();
        f.write(reinterpret_cast<const char*>(&r), sizeof(uint64_t));
    }
    f.close();
    return 0;
}