
#include "my_vector.h"


namespace {
    int32_t round_to_2_power(int n) {
        int result = 1;
        while (result < n) result *= 2;
        return result;
    }
}

namespace containers {
    template<typename T>
    my_vector<T>::my_vector() : array_(nullptr), capacity_(0), size_(0) {}

    template<typename T>
    my_vector<T>::my_vector(const my_vector &other)
                : capacity_(other.capacity_), size_(0) {
        if (&other == this) {
            return;
        }

        array_ = (T *) new char[capacity_ * sizeof(T)];
        for (int i = 0; i < other.size_; i++) {
            push_back(T(other[i]));
        }
    }

    template<typename T>
    my_vector<T>::my_vector(std::size_t n) : my_vector() {
        resize(n);
    }

    template<typename T>
    my_vector <T> &my_vector<T>::operator=(my_vector other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(array_, other.array_);

        return *this;
    }

    template<typename T>
    my_vector<T>::~my_vector() {
        if (array_ != nullptr) {
            clear();
            delete[](char *) array_;
        }
    }

    template<typename T>
    std::size_t my_vector<T>::size() const {
        return size_;
    }

    template<typename T>
    std::size_t my_vector<T>::capacity() const {
        return capacity_;
    }

    template<typename T>
    bool my_vector<T>::empty() const {
        return (size_ == 0);
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t n) {
        while (size_ > n)
            pop_back();

        reserve(n);

        while (size_ < n) {
            push_back(T());
        }
    }

    template<typename T>
    void my_vector<T>::reserve(std::size_t n) {
        if (n <= capacity_) return;

        my_vector<T> swapper;
        swapper.capacity_ = round_to_2_power(n);
        swapper.array_ = (T *) new char[swapper.capacity_ * sizeof(T)];

        for (int i = 0; i < size_; i++) {
            swapper.push_back(this->array_[i]);
        }
        *this = swapper;
    }

    template<typename T>
    T &my_vector<T>::operator[](std::size_t index) {
        return array_[index];
    }

    template<typename T>
    const T &my_vector<T>::operator[](std::size_t index) const {
        return array_[index];
    }


    template<typename T>
    void my_vector<T>::push_back(const T &t) {
        reserve(size_ + 1);
        new(&array_[size_++]) T(t);

    }

    template<typename T>
    void my_vector<T>::pop_back() {
        if (size_ == 0) return;
        size_--;
        array_[size_].~T();
    }

    template<typename T>
    void my_vector<T>::clear() {
        while (!empty()) pop_back();
    }

    template<typename R>
    std::ostream &operator<<(std::ostream &out, const my_vector <R> &vector) {
        out << vector.size() << " " << vector.capacity() << std::endl;
        for (std::size_t i = 0; i < vector.size_; ++i) {
            out << vector.array_[i] << (i + 1 < vector.size_ ? " " : "");
        }

        return out;
    }

}