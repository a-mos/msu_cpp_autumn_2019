#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <cmath>

//Some memory reserved for filenames/local variables ect.
constexpr size_t MAX_ELEMENTS_IN_MEMORY = 1024 * 1020;

auto split_to_files(std::ifstream &input, uint64_t* buff) {
    int f_idx = 0;
    input.seekg(0, input.end);
    size_t len = input.tellg() / sizeof(uint64_t);
    input.seekg(0, input.beg);
    size_t num_pairs = 2 * (size_t)std::ceil((float)len / MAX_ELEMENTS_IN_MEMORY);
    std::vector <std::string> out_names(num_pairs);
    for (size_t i = 0; i < num_pairs; ++i) {
        out_names[i] = std::to_string(i);
    }
    while (!input.eof()) {
        input.read(reinterpret_cast<char*>(buff), MAX_ELEMENTS_IN_MEMORY * sizeof(uint64_t));
        size_t readed = input.gcount() / sizeof(uint64_t);
        std::thread t1([buff, readed]() {
            std::sort(buff, buff + readed / 2);
        });
        std::thread t2([buff, readed]() {
            std::sort(buff + readed / 2, buff + readed);
        });
        t1.join();
        t2.join();
        std::ofstream f1(out_names[f_idx], std::ios::binary);
        std::ofstream f2(out_names[f_idx + 1], std::ios::binary);
        f1.write(reinterpret_cast<const char*>(buff), sizeof(uint64_t) * readed / 2);
        f2.write(reinterpret_cast<const char*>(buff + readed / 2), sizeof(uint64_t) * readed / 2);
        f1.close();
        f2.close();
        f_idx += 2;
    }
    input.close();
    return out_names;
}

//(((0)+1) + 2) + 3
void merge_files(std::vector <std::string> &names, uint64_t* buff) {
    for (size_t i = 0; i < names.size() - 1; ++i) {
        size_t pos = 0;
        uint64_t cur;
        std::ifstream f1(names[i], std::ios::binary);
        std::ifstream f2(names[i + 1], std::ios::binary);
        f1.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
        f2.seekg(0, f2.end);
        size_t len = f2.tellg() / sizeof(uint64_t);
        f2.seekg(0, f2.beg);
        f2.read(reinterpret_cast<char*>(buff), len * sizeof(uint64_t));
        f2.close();
        
        std::ofstream of(names[i + 1], std::ios::binary);
        while (pos < len && !f1.eof()) {
            if (cur > buff[pos]) {
                of.write(reinterpret_cast<const char*>(&buff[pos]), sizeof(uint64_t));
                pos++;
            } else if (cur < buff[pos]) {
                of.write(reinterpret_cast<const char*>(&cur), sizeof(uint64_t));
                f1.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
            } else {
                of.write(reinterpret_cast<const char*>(&cur), sizeof(uint64_t));
                of.write(reinterpret_cast<const char*>(&buff[pos]), sizeof(uint64_t));
                pos++;
                f1.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
            }
        }
        if (pos >= len) {
            while (!f1.eof()) {
                of.write(reinterpret_cast<const char*>(&cur), sizeof(uint64_t));
                f1.read(reinterpret_cast<char*>(&cur), sizeof(uint64_t));
            }
        } else if (f1.eof()) {
            of.write(reinterpret_cast<const char*>(&buff[pos]), sizeof(uint64_t) * (len - pos));
        }
        f1.close();
        of.close();
    }
}

void remove_tmp_files(std::vector <std::string> &names, const char *out_name) {
    auto num_files = names.size();
    std::rename(names[num_files - 1].c_str(), out_name);
    names.pop_back();
    for (auto &name: names) {
        std::remove(name.c_str());
    }
}

int main(const int argc, const char **argv) {
    uint64_t* buff = new uint64_t [MAX_ELEMENTS_IN_MEMORY];
    std::ifstream input(argv[1], std::ios::binary);
    auto names = split_to_files(input, buff);
    merge_files(names, buff);
    remove_tmp_files(names, argv[2]);
    delete [] buff;
    return 0;
}
