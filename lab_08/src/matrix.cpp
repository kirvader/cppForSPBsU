#include <utility>
#include "matrix.hpp"


Matrix::Matrix(std::size_t r, std::size_t c) {
    _rows = r;
    _cols = c;
    if (r * c == 0) {
        _data = nullptr;
        return;
    }
    _data = new int*[_rows];
    if (r * c != 0)
        *_data = new int[_rows * _cols];
    for (std::size_t cur_row = 0; cur_row < _rows; cur_row++) {
        if (cur_row != 0) _data[cur_row] = _data[cur_row - 1] + _cols;
        for (std::size_t cur_col = 0; cur_col < _cols; cur_col++)
            set(cur_row, cur_col, 0);
    }
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    return _data[i][j];
}

void Matrix::print(FILE* f) const{

    for (std::size_t cur_row = 0; cur_row < get_rows(); cur_row++) {
        for (std::size_t cur_col = 0; cur_col < get_cols(); cur_col++)
            fprintf(f, (cur_col == 0) ? "%d" : " %d", get(cur_row, cur_col));
        fprintf(f, "\n");
    }
}

bool Matrix::operator==(const Matrix& m) const{
    if (_rows != m.get_rows() || _cols != m.get_cols()) return false;

    for (std::size_t cur_row = 0; cur_row < _rows; cur_row++)
        for (std::size_t cur_col = 0; cur_col < _cols; cur_col++)
            if (get(cur_row, cur_col) != m.get(cur_row, cur_col)) return false;
    return true;
}

bool Matrix::operator!=(const Matrix& m) const{
    return !(m == *this);
}

Matrix& Matrix::operator+=(const Matrix& m) {
    for (std::size_t cur_row = 0; cur_row < _rows; cur_row++)
        for (std::size_t cur_col = 0; cur_col < _cols; cur_col++)
            _data[cur_row][cur_col] += m.get(cur_row, cur_col);

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    for (std::size_t cur_row = 0; cur_row < _rows; cur_row++)
        for (std::size_t cur_col = 0; cur_col < _cols; cur_col++)
            _data[cur_row][cur_col] -= m.get(cur_row, cur_col);
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {

    return (*this = *this * m);
}

Matrix Matrix::operator+(const Matrix& m) const {
    // from the task we know that sizes are good

    return (Matrix(*this) += m);
}

Matrix Matrix::operator-(const Matrix& m) const {
    // from the task we know that sizes are good

    return (Matrix(*this) -= m);
}

Matrix Matrix::operator*(const Matrix& m) const {
    // from the task we know that sizes are good
    Matrix result(get_rows(), m.get_cols());

    for (std::size_t cur_row = 0; cur_row < result._rows; cur_row++)
        for (std::size_t cur_col = 0; cur_col < result._cols; cur_col++) {
            int current_cell_sum = 0;
            for (std::size_t index = 0; index < get_cols(); index++)
                current_cell_sum += get(cur_row, index) * m.get(index, cur_col);
            result.set(cur_row, cur_col, current_cell_sum);
        }

    return result;
}

Matrix &Matrix::operator=(const Matrix &m) {
    if (this == &m) return *this;

    // refreshing data
    Matrix new_matrix(m);
    _cols = new_matrix.get_cols();
    _rows = new_matrix.get_rows();
    std::swap(_data, new_matrix._data);
    return *this;
}

Matrix::Matrix(const Matrix& matrix) {
    if (this == &matrix) return;


    // refresh sizes and _data
    _rows = matrix.get_rows();
    _cols = matrix.get_cols();

    if(_rows * _cols == 0) {
        _data = nullptr;
        return;
    }
    _data = new int*[_rows];
    _data[0] = new int[_rows * _cols];

    for (std::size_t cur_row = 0; cur_row < _rows; cur_row++) {
        if (cur_row != 0) _data[cur_row] = _data[cur_row - 1] + _cols;
        for (std::size_t cur_col = 0; cur_col < _cols; cur_col++)
            set(cur_row, cur_col, matrix.get(cur_row, cur_col));
    }
}

Matrix::~Matrix() {
    if (_data) {
        delete[] _data[0];
        delete[] _data;
        _data = nullptr;
    }
}



