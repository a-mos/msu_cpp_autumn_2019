using namespace std;

class Proxy_Class {
    int *data;
    size_t cols;
public:
    Proxy_Class(int *data, size_t cols): data(data), cols(cols) {}
    
    int &operator[] (size_t pos) {
        if (pos < cols) {
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
    
    size_t getRows() const {
        return rows;
    }
    
    size_t getColumns() const {
        return cols;
    }
    
    Proxy_Class operator[] (size_t pos) {
        if (pos < rows) {
            return Proxy_Class(data[pos], cols);
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
    
    bool operator== (const Matrix &right) const {
        if (rows == right.getRows() && cols == right.getColumns()) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (data[i][j] != right.data[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }
    
    bool operator!= (const Matrix &right) const {
        return !(*this == right);
    }
    
    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete [] data[i];
        }
        delete [] data;
    }
};
