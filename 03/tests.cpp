#include <iostream>
#include "matrix.h"
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        const size_t rows = 5;
        const size_t cols = 3;
        Matrix m1(rows, cols);
        Matrix m2(rows, cols);
        switch (atoi(argv[1])) {
            case 1:
                assert(m1.getRows() == 5);
                break;
            case 2:
                assert(m1.getColumns() == 3);
                break;
            case 3:
                assert(m1 == m2);
                break;
            case 4:
                m1[1][2] = 10;
                m2[1][2] = 20;
                assert(m1 != m2);
                break;
            case 5:
                m1[1][2] = 10;
                m2[1][2] = 20;
                assert(m1 != m2);
                m2[1][2] = 10;
                assert(m1 == m2);
                break;
            case 6:
                m1[1][2] = 10;
                m2[2][1] = 5;
                m1 *= 10;
                m2 *= 5;
                assert(m1[1][2] == 100);
                assert(m2[2][1] == 25);
                break;
            case 7:
                assert(m1 == m1);
                m1[0][0] = 1;
                assert(m1 != m2);
                break;
            case 8:
                try {
                    m1[1][10] = 0;
                } catch (...) {
                    cout << "out_of_range" << endl;
                }
                break;
            case 9:
                try {
                    m1[-1][1] = 0;
                } catch (...) {
                    cout << "out_of_range" << endl;
                }
                break;
            default:
                break;
        }
        cout << "done" << endl;
    } else {
        Matrix m1(5, 3);
        cout << "Matrix 5x3" << endl;
        cout << "Rows: " << m1.getRows() << endl;
        cout << "Cols: " << m1.getColumns() << endl;
    }
    return 0;
}
