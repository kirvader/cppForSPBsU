#pragma once

#include "matrix.hpp"

class shared_ptr {
public:
    /**
     * Получает объект по сырому указателю во владение.
     * Передача того же указателя во владение кому либо ещё — неопределённое поведение.
     */
    shared_ptr(Matrix* obj = nullptr);
    /**
     * Строит копию умного указателя, разделяя владение с оригиналом.
     */
    shared_ptr(const shared_ptr& other);
    /**
     * Присваивает умному указателю новое значение, корректно меняя владение с одного объекта на другой.
     */
    shared_ptr& operator=(shared_ptr other);
    ~shared_ptr();

    /**
     * Возвращает сырой указатель для несовместимого кода.
     */
    Matrix* ptr() const;
    /**
     * Проверка на nullptr.
     */
    bool isNull() const { return storage_ == nullptr || storage_->getObject() == nullptr; };
    /**
     * Присваивает умному указателю новый для владения.
     */
    void reset(Matrix* obj = nullptr);

    Matrix* operator->() const;
    Matrix& operator*() const;

private:

    class Storage {
    public:
        Storage(Matrix* mtx);
        ~Storage();

        void incr() { ref_count_++; };
        void decr() { ref_count_--; };

        int getCounter() const {
            return ref_count_;
        }

        Matrix* getObject() const {
            return data_;
        };

    private:
        Matrix *data_;
        int ref_count_;
    };

    void incrRefCounterAndReplace(const shared_ptr& other) {
        storage_ = other.storage_;
        if (storage_)
            storage_->incr();
    };

    void deleteOneRef() {
        if (storage_ == nullptr)
            return;

        storage_->decr();
        if (storage_->getCounter() == 0)
            delete storage_;
    };

    Storage* makeStorage(Matrix* matrix) const {
        return (matrix != nullptr) ? new Storage(matrix) : nullptr;
    };

private:
    Storage *storage_;
};