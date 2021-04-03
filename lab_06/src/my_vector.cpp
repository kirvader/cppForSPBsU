//
// Created by kira on 18.02.2021.
//

#include "my_vector.h"
#include "utility"

MyVector::MyVector() {
    _cp = 2;
    _data = new int[_cp];
    _sz = 0;
}
MyVector::MyVector(std::size_t init_capacity) {
    _cp = init_capacity;
    _data = new int[_cp];
    _sz = 0;
}
MyVector::~MyVector() {
    delete [] _data;
}

void MyVector::set(std::size_t index, int value) {
    if (index < _cp)
        _data[index] = value;
}
int MyVector::get(std::size_t index) const {
    return _data[index];
}

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity > _cp) {
        int *new_data = new int[new_capacity];
        for (int index = 0; index < _sz; index++) {
            new_data[index] = _data[index];
        }
        delete _data;
        _data = new_data;
        _cp = new_capacity;
    }
}
void MyVector::resize(std::size_t new_size) {
    if (new_size > _cp) {
        std::size_t new_cp = new_size;
        if (2 * _cp > new_size) new_cp = 2 * _cp;
        reserve(new_cp);
    }
    if (new_size > _sz)
        for (int cur_index = _sz; cur_index < new_size; cur_index++)
            _data[cur_index] = 0;
    _sz = new_size;
}

void MyVector::push_back(int value) {
    if (_sz == _cp)
        reserve(2 * _cp);
    _data[_sz] = value;
    _sz++;
}
void MyVector::insert(std::size_t index, int value) {
    if (_sz == _cp)
        reserve(2 * _cp);
    for (int cur_index = index + 1; cur_index <= _sz; cur_index++) {
        _data[cur_index] = _data[cur_index - 1];
    }
    _sz++;
    _data[index] = value;
}
void MyVector::erase(std::size_t index) {
    if (index < 0 && index >= _sz)
    for (int i = index; i < _sz - 1; i++) {
        _data[i] = _data[i + 1];
    }
    _sz--;
}

MyVector::MyVector(const MyVector& vector) {
    if (&vector == this)
        return;

    _sz = vector._sz;
    _cp = vector._cp;
    _data = new int[_cp];
    for (int index = 0; index < _sz; index++) {
        _data[index] = vector.get(index);
    }
}

MyVector &MyVector::operator =(const MyVector &vector) {
    if (&vector == this) {
        return *this;
    }

    delete _data;

    _sz = vector._sz;
    _cp = vector._cp;
    _data = new int[_cp];
    for (int index = 0; index < _sz; index++) {
        _data[index] = vector.get(index);
    }

    return *this;
}
