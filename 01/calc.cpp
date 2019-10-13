// Grammar:
// S = T {("+" | "-") T}
// T = F {("*" | "/") F}
// F = {"-"} D {D}
// D = ("0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9")
#include <iostream>
#include <string>
using namespace std;
string s;
int pos = -1;
int T();
int F();
int S() {
    int value = T();
    while (s[pos + 1] == '-' || s[pos + 1] == '+') {
        int op = s[++pos];
        int next_value = T();
        if (op == '+') {
            value += next_value;
        } else {
            value -= next_value;
        }
    }
    return value;
}

int T() {
    int value = F();
    while (s[pos + 1] == '*' || s[pos + 1] == '/') {
        int op = s[++pos];
        int next_value = F();
        if (op == '/') {
            if (next_value == 0) {
                throw "Division by zero";
            }
            value /= next_value;
        } else {
            value *= next_value;
        }
    }
    return value;
}

int F() {
    bool negative = false;
    while (s[pos + 1] == '-') {
        negative = !negative;
        pos++;
    }
    int number = 0;
    if (!isdigit(s[pos + 1])) {
        throw "Invalid expression";
    }
    while (isdigit(s[pos + 1])) {
        int dig = s[++pos] - '0';
        number = 10 * number + dig;
    }
    if (negative) {
        return -number;
    } else {
        return number;
    }
}

int main(int argc, char* argv[]) {
    for (size_t i = 0; i < strlen(argv[1]); ++i) {
        if (isspace(argv[1][i])) {
             continue;
        } else if (isdigit(argv[1][i]) || argv[1][i] == '+' \
            || argv[1][i] == '-' || argv[1][i] == '*' || argv[1][i] == '/') {
            s += argv[1][i];
        } else {
            cout << "Invalid expression" << endl;
            return 1;
        }
    }
    try {
        int ans = S();
        cout << ans << endl;
    } catch (const char *err) {
        cout << err << endl;
        return 1;
    }
}
