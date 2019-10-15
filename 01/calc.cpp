// Grammar:
// Start = Sum {("+" | "-") Sum}
// Sum = Factor {("*" | "/") Factor}
// Factor = {"-"} Digit {Digit}
// Digit = ("0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9")
#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

int Sum(const string &s, size_t &pos);
int Factor(const string &s, size_t &pos);
int Start(const string &s) {
    size_t pos = -1;
    int value = Sum(s, pos);
    while (s[pos + 1] == '-' || s[pos + 1] == '+') {
        int op = s[++pos];
        int next_value = Sum(s, pos);
        if (op == '+') {
            value += next_value;
        } else {
            value -= next_value;
        }
    }
    return value;
}

int Sum(const string &s, size_t &pos) {
    int value = Factor(s, pos);
    while (s[pos + 1] == '*' || s[pos + 1] == '/') {
        int op = s[++pos];
        int next_value = Factor(s, pos);
        if (op == '/') {
            if (next_value == 0) {
                throw invalid_argument("Division by zero");
            }
            value /= next_value;
        } else {
            value *= next_value;
        }
    }
    return value;
}

int Factor(const string &s, size_t &pos) {
    bool negative = false;
    while (s[pos + 1] == '-') {
        negative = !negative;
        pos++;
    }
    int number = 0;
    if (!isdigit(s[pos + 1])) {
        throw invalid_argument("Invalid expression");
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

void get_string(string &s, const char* argv) {
    for (size_t i = 0; i < strlen(argv); ++i) {
        if (isspace(argv[i])) {
            continue;
        } else if (isdigit(argv[i]) || argv[i] == '+' \
                   || argv[i] == '-' || argv[i] == '*' || argv[i] == '/') {
            s += argv[i];
        } else {
            throw invalid_argument("Invalid expression");
        }
    }
}

int main(int argc, const char* argv[]) {
    if (argc == 2) {
        try {
            string s;
            get_string(s, argv[1]);
            int ans = Start(s);
            cout << ans << endl;
        } catch (exception &err) {
            cout << err.what() << endl;
            return 1;
        }
    } else {
        cout << "No expression" << endl;
        return 1;
    }
    return 0;
}
