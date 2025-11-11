#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <stdexcept>
#include <ostream>

template<typename T>
class ListArray {
private:
    T* arr;
    int max;
    int n;
    static const int MINSIZE = 2;

    void resize(int new_size) {
        if (new_size < MINSIZE) new_size = MINSIZE;
        T* new_arr = new T[new_size];
        for (int i = 0; i < n; ++i)
            new_arr[i] = arr[i];
        delete[] arr;
        arr = new_arr; 
        max = new_size;

public:
    ListArray() {
        arr = new T[MINSIZE];
        max = MINSIZE;
        n = 0;
    }

    ~ListArray() {
        delete[] arr; 
    }


    void insert(int pos, T e) {
        if (pos < 0 || pos > n) 
            throw std::out_of_range("insert: posición inválida");
        
        if (n == max) resize(max * 2);

        for (int i = n; i > pos; i--) 
            arr[i] = arr[i - 1];
        arr[pos] = e;
        n++; 
    }

    void append(T e) {
        insert(n, e);
    }

    void prepend(T e) {
        insert(0, e); 
    }

    int search(T e) {
        for (int i = 0; i < n; ++i) {
            if (arr[i] == e) return i; 
        }
        return -1;  
    }


    T remove(int pos) {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("remove: posición inválida");
        T value = arr[pos];
        for (int i = pos; i < n - 1; i++)
            arr[i] = arr[i + 1];
        n--;
        
        if (n <= max / 4) resize(max / 2);
        return value;
    }

    T& operator[](int pos) {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("operator[]: fuera de rango");
        return arr[pos];
    }

    T get(int pos) const {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("get: fuera de rango");
        return arr[pos];
    }

    int size() const { return n; }

    bool empty() const { return n == 0; }

    friend std::ostream& operator<<(std::ostream& out, const ListArray<T>& list) {
        out << "[";
        for (int i = 0; i < list.n; ++i) {
            out << list.arr[i];
            if (i + 1 < list.n) out << ", ";
        }
        out << "]";
        return out;
    }
};
};
#endif