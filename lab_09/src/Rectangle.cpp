#include <cstdio>
#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y), width(width), height(height) {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int x, int y) const {
    return (2 * x >= 2 * this->x - width && 2 * x <= 2 * this->x + width) &&
                (2 * y >= 2 * this->y - height && 2 * y <= 2 * this->y + height);
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}


