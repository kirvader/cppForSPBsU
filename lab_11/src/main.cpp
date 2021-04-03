#include <iostream>
#include <cstring>
#include <cassert>

#include "my_vector.h"

namespace product {

    class Product {
    public:
        Product(const char *name, int quantity, double price);

        ~Product();

        Product(const Product &other);

        Product& operator=(Product other);

        bool operator==(const Product &other) const;

        friend std::ostream &operator<<(std::ostream &out, const Product &val);

    private:
        char *name_;  // Указатель владеет C-style строкой, на которую указывает.
        int quantity_;
        double price_;
    };

    Product::Product(const char *name, int quantity, double price) :
            quantity_(quantity), price_(price) {
        int32_t str_len = strlen(name) + 1;
        name_ = new char[str_len];
        strcpy(name_, name);
        name_[str_len - 1] = '\0';
    }

    std::ostream &operator<<(std::ostream &out, const Product &val) {
        out << val.name_ << " " << val.quantity_ << " " << val.price_ << '\n';
        return out;
    }

    Product::~Product() {
        delete[] name_;
    }

    Product::Product(const Product &other)
            : quantity_(other.quantity_), price_(other.price_) {

        if (this == &other) {
            return;
        }

        int32_t str_len = strlen(other.name_) + 1;
        name_ = new char[str_len];
        strcpy(name_, other.name_);
        name_[str_len - 1] = '\0';
    }

    bool Product::operator==(const Product &other) const {
        return (price_ == other.price_) && (quantity_ == other.quantity_) && (strcmp(name_, other.name_) == 0);
    }

    Product &Product::operator=(Product other) {
        std::swap(name_, other.name_);
        std::swap(quantity_, other.quantity_);
        std::swap(price_, other.price_);
        return *this;
    }



    void print(const containers::my_vector<Product> &v) {
        std::cout << v << std::endl;
    }

}  // namespace product


namespace testing {
    using containers::my_vector;

    template<typename T>
    void test_my_vector(const T &first, const T &second) {

        my_vector<T> vector1;
        vector1.push_back(first);
        assert(vector1[0] == first);


        my_vector<T> vector2 = vector1;
        assert(vector1[0] == vector2[0]);
        assert(vector2.capacity() == 1);

        vector1.clear();
        assert(vector1.empty());
        assert(!vector2.empty());

        vector2.push_back(second);
        assert(vector2.size() == 2);

        my_vector<T> vector3(vector2);
        assert(vector3[1] == vector2[1]);
        vector3.push_back(first);
        assert(vector3[2] == first);
        assert(vector3.size() == 3);
        assert(vector3.capacity() == 4);

        vector1.reserve(5);
        assert(vector1.capacity() == 8);
        assert(vector1.empty());
        vector1 = vector3;
        assert(vector3[2] == vector1[2]);

        vector1[1] = first;
        assert(vector1[1] == first);
        assert(vector1[0] == vector3[0]);

        vector1.pop_back();
        assert(vector1.size() == 2);
        assert(vector1.capacity() == 4);


        vector3.clear();
        assert(vector3.empty());
        assert(vector3.capacity() == 4);

    }

    template<typename T>
    void test_my_vector_default_constructable(const T &first, const T &second) {
        my_vector<T> vector1(5);
        assert(vector1.size() == 5);
        assert(vector1.capacity() == 8);

        vector1[0] = first;
        vector1[3] = second;
        vector1.push_back(second);
        vector1.push_back(first);
        assert(vector1.size() == 7);
        assert(vector1[3] == second);
        assert(vector1[0] == first);

        vector1.resize(3);
        vector1[2] = second;
        assert(vector1.size() == 3);
        assert(vector1[2] == second);
        vector1.resize(7);
        assert(vector1.size() == 7);

    }
}

int main() {
    testing::test_my_vector<int>(5, 10);
    testing::test_my_vector_default_constructable<int>(5, 10);
    testing::test_my_vector<product::Product>
            (product::Product("asdf", 4, 12.0),
             product::Product("qwe", -1, 7.5));
    std::cout << "All tests passed";
    return 0;
}
