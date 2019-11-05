#include <iostream>
#include <cstring>
using namespace std;

class BigInt {
    char *data;
    size_t max_size = 16;
    size_t cur_size = 0;
    bool sign = false;
public:
    BigInt(int64_t num = 0) {
        data = new char[max_size]();
        if (num < 0) {
            sign = true;
            Store(-(num % 10));
            num /= 10;
            num = -num;
        }
        while (num) {
            Store(num % 10);
            num /= 10;
        }
    }
    
    BigInt(const BigInt &r) {
        sign = r.sign;
        max_size = r.max_size;
        cur_size = r.cur_size;
        data = new char[max_size]();
        memcpy(data, r.data, max_size);
    }
    
    void Store(char num) {
        if (cur_size == max_size) {
            char *new_data = new char[max_size * 2]();
            memcpy(new_data, data, max_size);
            max_size *= 2;
            delete [] data;
            data = new_data;
        }
        data[cur_size] = num;
        cur_size += 1;
    }

    bool operator==(const BigInt &r) const {
        if (cur_size != r.cur_size || sign != r.sign) {
            return false;
        } else {
            return !memcmp(data, r.data, cur_size);
        }
    }
    
    bool operator!=(const BigInt &r) const {
        return !(*this == r);
    }
    
    bool operator<(const BigInt &r) const {
        if (sign && !r.sign) {
            return true;
        } else if (!sign && r.sign) {
            return false;
        }
        if (cur_size < r.cur_size) {
            return !sign;
        } else if (cur_size > r.cur_size) {
            return sign;
        }
        for (size_t i = 1; i <= cur_size; ++i) {
            char diff = data[cur_size - i] - r.data[cur_size - i];
            if (diff < 0) {
                return !sign;
            } else if (diff > 0) {
                return sign;
            }
        }
        //==
        return false;
    }
    
    bool operator>(const BigInt &r) const {
        return (*this != r && !(*this < r));
    }
    
    bool operator>=(const BigInt &r) const {
        return !(*this < r);
    }
    
    bool operator<=(const BigInt &r) const {
        return !(*this > r);
    }
    
    BigInt operator-() const {
        BigInt ans(*this);
        ans.sign = !ans.sign;
        return ans;
    }
    
    BigInt operator+(const BigInt &r) const {
        // - + +
        if (sign && !r.sign) {
            return r - -(*this);
        }
        // + + -
        if (!sign && r.sign) {
            return *this - (-r);
        }
        char add = 0;
        char sum = 0;
        if (r.cur_size > cur_size) {
            BigInt ans(r);
            for (size_t i = 0; i < r.cur_size; ++i) {
                sum = ans.data[i] + data[i] + add;
                ans.data[i] = sum % 10;
                add = sum / 10;
            }
            if (add) {ans.Store(add);}
            return ans;
        } else {
            BigInt ans(*this);
            for (size_t i = 0; i < cur_size; ++i) {
                sum = ans.data[i] + r.data[i] + add;
                ans.data[i] = sum % 10;
                add = sum / 10;
            }
            if (add) {ans.Store(add);}
            return ans;
        }
    }
    
    BigInt operator-(const BigInt &r) const {
        // - - +
        if (sign && !r.sign) {
            return -(-r + *this);
        }
        // - - -
        if (sign && r.sign) {
            return *this + -r;
        }
        // + - -
        if (!sign && r.sign) {
            return *this + -r;
        }
        if (r > *this) {
            return -(r - *this);
        }
        BigInt ans(*this);
        char sub = 0;
        char diff = 0;
        for (size_t i = 0; i < cur_size; ++i) {
            if (i < r.cur_size) {
                diff = ans.data[i] - r.data[i] - sub;
            } else {
                diff = ans.data[i] - sub;
            }
            if (diff < 0) {
                ans.data[i] = 10 + diff;
                sub = 1;
            } else {
                ans.data[i] = diff;
                sub = 0;
            }
        }
        while ((ans.cur_size - 1) && !ans.data[ans.cur_size - 1]) {
            ans.cur_size -= 1;
        }
        return ans;
    }
    friend ostream& operator<<(ostream& os, const BigInt &r);
    ~BigInt() {
        delete [] data;
    }
};

ostream& operator<< (ostream &os, const BigInt &r) {
    if (r.sign) {
        os << '-';
    }
    for (size_t i = 1; i <= r.cur_size; ++i) {
        os << char(r.data[r.cur_size - i] + '0');
    }
    return os;
}
