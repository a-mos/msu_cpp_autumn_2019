using namespace std;

class Proxy_Class {
    int *data;
public:
    Proxy_Class(int *data): data(data) {}
    
    int &operator[] (int pos) {
        if (pos <= sizeof(data) / sizeof(*data) && pos >= 0) {
            return data[pos];
        } else {
            throw std::out_of_range("");
        }
    }
};

class Matrix {
    size_t rows;
    size_t cols;
    int **data;
public:
    Matrix(size_t rows, size_t cols): rows(rows), cols(cols) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols]();
        }
    }
    
    size_t getRows() {
        return rows;
    }
    
    size_t getColumns() {
        return cols;
    }
    
    Proxy_Class &operator[] (int pos) {
        if (pos < rows && pos >= 0) {
            return *(new Proxy_Class(data[pos]));
        } else {
            throw std::out_of_range("");
        }
    }
    
    Matrix& operator*= (int num) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] *= num;
            }
        }
        return *this;
    }
    
    bool operator== (Matrix &right) {
        if (rows == right.getRows() && cols == right.getColumns()) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (data[i][j] != right[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }
    
    bool operator!= (Matrix &right) {
        return !(*this == right);
    }
    
    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete [] data[i];
        }
        delete [] data;
    }
};
