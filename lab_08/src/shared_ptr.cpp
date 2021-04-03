#include "shared_ptr.hpp"


shared_ptr::shared_ptr(Matrix *obj) : storage_(makeStorage(obj)) {}

shared_ptr::shared_ptr(const shared_ptr &other) {
    if (this == &other) return;
    incrRefCounterAndReplace(other);
}

shared_ptr &shared_ptr::operator=(shared_ptr other) {
    deleteOneRef();
    incrRefCounterAndReplace(other);
    return *this;
}

shared_ptr::~shared_ptr() {
    deleteOneRef();
}

Matrix *shared_ptr::ptr() const {
    return (storage_ != nullptr) ? storage_->getObject() : nullptr;
}


void shared_ptr::reset(Matrix *obj) {
    deleteOneRef();
    storage_ = makeStorage(obj);
}

Matrix *shared_ptr::operator->() const {
    return ptr();
}

Matrix &shared_ptr::operator*() const {
    return *(storage_->getObject());
}


shared_ptr::Storage::Storage(Matrix *mtx) : data_(mtx), ref_count_(1) {}


shared_ptr::Storage::~Storage() {
    delete data_;
}
