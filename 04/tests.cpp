#include <iostream>
#include <limits.h>
#include "BigInt.h"
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc > 1) {
    	BigInt a = 1;
    	BigInt b = 1;
    	BigInt c(a + b);
    	BigInt d = LLONG_MAX;
        switch (atoi(argv[1])) {
            case 1:
                assert(a == b);
                break;
            case 2:
                assert(!(a != b));
                break;
            case 3:
            	cout << d + d;
                break;
            case 4:
                cout << d + d - (d - a) + c - b;
                break;
            case 5:
                cout << -c;
                break;
            case 6:
                cout << -d - -d;
                break;
            case 7:
                assert(a <= b);
                break;
            case 8:
                assert(a < c);
                break;
            case 9:
                assert(c >= b);
                break;
            case 10:
               	assert(a <= b && a < c && a < d && d == d && d > d - 1);
                break;
            case 11:
                cout << a - a - a - a - a - a;
                break;
            default:
                break;
        }
        cout << "done" << endl;
    } else {
        BigInt a = 1;
		BigInt b = a;
		BigInt c = a + b + 2;
		cout << c << endl;
    }
    return 0;
}
