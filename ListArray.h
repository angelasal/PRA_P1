
#ifndef LISTARRAY_H
#define LISTARRAY_H

#include "List.h"
#include <stdexcept>
#include <iostream>

// Clase genérica que implementa una lista usando un array dinámico
template <typename T>
class ListArray : public List<T> {
private:
    T* data;
    int capacity;
    int count;

    void resize(int new_capacity) {
        T* new_data = new T[new_capacity];
        for (int i = 0; i < count; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    ListArray(int init_capacity = 10) {
        data = new T[init_capacity];
        capacity = init_capacity;
        count = 0;
    }

    ~ListArray() {
        delete[] data;
    }

    void insert(int pos, T e) override {
        if (pos < 0 || pos > count) {
            throw std::out_of_range("Posición inválida en insert()");
        }
        if (count == capacity) {
            resize(capacity * 2);
        }
        for (int i = count; i > pos; --i) {
            data[i] = data[i - 1];
        }
        data[pos] = e;
        ++count;
    }

    void append(T e) override {
        insert(count, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= count) {
            throw std::out_of_range("Posición inválida en remove()");
        }
        T removed = data[pos];
        for (int i = pos; i < count - 1; ++i) {
            data[i] = data[i + 1];
        }
        --count;
        return removed;
    }

    T get(int pos) const override {
        if (pos < 0 || pos >= count) {
            throw std::out_of_range("Posición inválida en get()");
        }
        return data[pos];
    }

    int search(T e) override {
        for (int i = 0; i < count; ++i) {
            if (data[i] == e) {
                return i;
            }
        }
        return -1;
    }

    bool empty() override {
        return count == 0;
    }

    int size() const override {
        return count;
    }

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }
};

// Sobrecarga del operador << para imprimir ListArray<T>
template <typename T>
std::ostream& operator<<(std::ostream& os, const ListArray<T>& list) {
    os << "[";
    for (int i = 0; i < list.size(); ++i) {
        os << list.get(i);
        if (i < list.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}

#endif // LISTARRAY_H
