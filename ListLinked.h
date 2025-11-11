#ifndef LISTLINKED_H
#define LISTLINKED_H

#include "List.h"
#include <stdexcept>
#include <ostream>

template<typename T>
class ListLinked : public List<T> {

private:
    struct Node { 
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };
    Node* first;
    int n;


public:
    ListLinked() : first(nullptr), n(0) {}

    ~ListLinked() {
        while (first != nullptr) {
            Node* temp = first;
            first = first->next;
            delete temp;
        }
    }


    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) throw std::out_of_range("insert: posición inválida");
        Node* nuevo = new Node(e);
        if (pos == 0) {
            nuevo->next = first;
            first = nuevo;
        } else {
            Node* aux = first;
            for (int i = 0; i < pos - 1; i++) aux = aux->next;
            nuevo->next = aux->next;
            aux->next = nuevo;
        }
        n++;
    }

    void append(T e) override { insert(n, e); }

    void prepend(T e) override { insert(0, e); }


    T remove(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("remove: posición inválida");
        Node* to_delete;
        T value;
        if (pos == 0) {
            to_delete = first;
            value = to_delete->data;
            first = first->next;
        } else {
            Node* aux = first;
            for (int i = 0; i < pos - 1; ++i) aux = aux->next;
            to_delete = aux->next;
            value = to_delete->data;
            aux->next = to_delete->next;
        }
        delete to_delete;
        n--;
        return value;
    }


    T& operator[](int pos) {
        if (pos < 0 || pos >= n) throw std::out_of_range("operator[]: fuera de rango");
        Node* aux = first;
        for (int i = 0; i < pos; ++i) aux = aux->next;
        return aux->data;
    }


    T get(int pos) const override {
        if (pos < 0 || pos >= n) throw std::out_of_range("get: posición inválida");
        Node* aux = first;
        for (int i = 0; i < pos; ++i) aux = aux->next;
        return aux->data;
    }


    int search(T e) override {
        Node* aux = first;
        int idx = 0;
        while (aux != nullptr) {
            if (aux->data == e) return idx;
            aux = aux->next;
            ++idx;
        }
        return -1;
    }


    bool empty() override { return n == 0; }

    int size() const override { return n; }


    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        out << "[";
        Node* aux = list.first;
        while (aux != nullptr) {
            out << aux->data;
            aux = aux->next;
            if (aux != nullptr) out << ", ";
        }
        out << "]";
        return out;
    }
};

#endif
