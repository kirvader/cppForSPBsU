#ifndef LAB_07_MATRIX_H
#define LAB_07_MATRIX_H


#include <cstdio>
#include <cstddef>

class Matrix {
public:
    Matrix(std::size_t r = 0, std::size_t c = 0);
    Matrix(const Matrix& matrix);
    ~Matrix();

    std::size_t get_rows() const { return _rows; }
    std::size_t get_cols() const { return _cols; }
    void set(std::size_t i, std::size_t j, int val);
    int get(std::size_t i, std::size_t j) const;
    void print(FILE *f) const;

    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;

    Matrix& operator=(const Matrix& m);
    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);

    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;
private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
};


#endif //LAB_07_MATRIX_H
