#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>

namespace containers {

template<typename T>
class my_vector {
public:
    my_vector();//
    explicit my_vector(std::size_t n);
    my_vector(const my_vector& other);//
    my_vector& operator=(my_vector other);//
    ~my_vector();//

    [[nodiscard]] std::size_t size() const; //
    [[nodiscard]] std::size_t capacity() const; //
    [[nodiscard]] bool empty() const; //

    void resize(std::size_t n);
    void reserve(std::size_t n); //

    T& operator[](std::size_t index); //
    const T& operator[](std::size_t index) const; //

    void push_back(const T &t); //
    void pop_back(); //
    void clear(); //
    template<typename R>
    friend std::ostream &operator<<(std::ostream &out, const my_vector<R> &vector);

private:
    size_t capacity_{};
    size_t size_{};
    T* array_;
};

}

#include "my_vector_impl.h"

#endif  //MY_VECTOR_H_
