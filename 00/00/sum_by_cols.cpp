#include <iostream>
#include <random>
#include <chrono>

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
    : start_(clock_t::now())
    {
    }
    
    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us =
        std::chrono::duration_cast<microseconds>
        (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }
    
private:
    const clock_t::time_point start_;
};

using namespace std;
struct matrix {
    int ** _data;
    size_t size;
    matrix (size_t n) {
        size = n;
        _data = static_cast<int **>(calloc(n, sizeof(int *)));
        for (int i = 0; i < n; ++i) {
            _data[i] = static_cast<int *>(calloc(n, sizeof(int)));
        }
    }
    ~matrix() {
        for (int i = 0; i < size; ++i) {
            free(_data[i]);
        }
        free(_data);
    }
    void set_matrix_random_numbers() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution <int> uid(-10, 10);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                _data[i][j] = uid(gen);
            }
        }
    }
};



int main(int argc, const char * argv[]) {
    //By-Cols
    volatile int result = 0;
    const size_t MATRIX_SIZE = 10000;
    matrix A(MATRIX_SIZE);
    A.set_matrix_random_numbers();
    Timer t;
    for (int i = 0; i < A.size; ++i) {
        for (int j = 0; j < A.size; ++j) {
            result += A._data[j][i];
        }
    }
    //cout << result << endl;
    return 0;
}
