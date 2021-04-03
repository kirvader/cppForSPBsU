#include "Scheme.hpp"
#include "Figure.hpp"

Scheme::Scheme(int capacity) : figures_(new Figure*[capacity]), cp_(capacity) {}

Scheme::~Scheme() {
    for (int i = 0; i < sz_; i++) {
        delete figures_[i];
    }
    delete []figures_;
}

void Scheme::push_back_figure(Figure *fg) {
    if (sz_ == cp_) return; // если некуда складывать фигуры, то это габелла
    figures_[sz_++] = fg;
}

void Scheme::remove_figure(int id) {
    int currentIndex = findIndexById(id);
    while (currentIndex < sz_ && figures_[currentIndex]->getId() != id)
        currentIndex++;

    if (currentIndex == sz_) // значит нет такого id
        return;

    delete figures_[currentIndex++];
    while (currentIndex < sz_) {
        figures_[currentIndex - 1] = figures_[currentIndex];
        currentIndex++;
    }
    sz_--;
}

void Scheme::print_all_figures() const {
    for (int index = 0; index < sz_; index++) {
        figures_[index]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) const {
    int figureIndex = findIndexById(id);
    figures_[figureIndex]->zoom(factor);
}

Figure *Scheme::is_inside_figure(int x, int y) const {
    for (int index = 0; index < sz_; index++) {
        if (figures_[index]->is_inside(x, y))
            return figures_[index];
    }
    return nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
    int figureIndex = findIndexById(id);
    figures_[figureIndex]->move(new_x, new_y);
}

int Scheme::findIndexById(const int id) const {
    int currentIndex = 0;
    while (currentIndex < sz_ && figures_[currentIndex]->getId() != id)
        currentIndex++;
    return currentIndex;
}

