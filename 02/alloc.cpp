#include <iostream>
using namespace std;

class LinearAllocator {
    size_t max_size;
    size_t cur_size;
    char *start;
    char *cur_pos;
public:
    LinearAllocator(size_t maxSize) {
        max_size = maxSize;
        cur_size = 0;
        start = static_cast<char *>(malloc(maxSize));
        cur_pos = start;
    }
    char* alloc(size_t size) {
        if (size == 0 || cur_size + size > max_size) {
            return nullptr;
        }
        char *allocated= cur_pos;
        cur_size += size;
        cur_pos += size;
        return allocated;
    }
    void reset() {
        cur_pos = start;
        cur_size = 0;
    }
    size_t get_max_size() {
        return max_size;
    }
    size_t get_cur_size() {
        return cur_size;
    }
    ~LinearAllocator() {
        max_size = cur_size = 0;
        free(start);
    }
};

int main(int argc, const char * argv[]) {
    if (argc > 1) {
        LinearAllocator allocator(atoi(argv[1]));
        for (int i = 0; i < argc; ++i) {
            if (strstr(argv[i], "alloc") == argv[i]) {
                auto size = atoi(argv[i] + strlen("alloc"));
                auto tmp = allocator.alloc(size);
                cout << (tmp ? "Allocated: " :  "Not allocated: ") << size << endl;
            } else if (strstr(argv[i], "cursize") == argv[i]) {
                cout << "Cur size: " << allocator.get_cur_size() << endl;
            } else if (strstr(argv[i], "maxsize") == argv[i]) {
                cout << "Max size: " << allocator.get_max_size() << endl;
            } else if (strstr(argv[i], "reset") == argv[i]) {
                allocator.reset();
                cout << "Reset" << endl;
            }
        }
    } else {
        cout << "No input" << endl;
        return 1;
    }
}
