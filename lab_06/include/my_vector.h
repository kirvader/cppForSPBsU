//
// Created by kira on 18.02.2021.
//

#ifndef LAB_06_MY_VECTOR_H
#define LAB_06_MY_VECTOR_H

#include <cstddef>

class MyVector {
public: // methods
    MyVector();
    MyVector(std::size_t init_capacity);
    MyVector(const MyVector& vector);
    MyVector& operator =(const MyVector& vector);
    ~MyVector();

    void set(std::size_t index, int value);
    int get(std::size_t index) const;

    std::size_t size() const { return _sz; }
    std::size_t capacity() const { return _cp; }

    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size);

    void push_back(int value);
    void insert(std::size_t index, int value);
    void erase(std::size_t index);
private: // fields
    std::size_t _sz, _cp;
    int *_data;
};

#endif //LAB_06_MY_VECTOR_H
