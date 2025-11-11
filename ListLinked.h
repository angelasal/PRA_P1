#ifndef LISTLINKED_H
#define LISTLINKED_H

#include "List.h"        // interfaz List<T>
#include <stdexcept>     // para std::out_of_range
#include <ostream>       // para operator<<

template<typename T>
class ListLinked : public List<T> {
private:
    struct Node {          // nodo interno sencillo
        T data;            // dato almacenado
        Node* next;        // puntero al siguiente nodo
        Node(T d) : data(d), next(nullptr) {} // constructor del nodo
    };

    Node* first;           // puntero al primer nodo de la lista
    int n;                 // número de elementos que contiene la lista

public:
    // constructor: lista vacía
    ListLinked() : first(nullptr), n(0) {}

    // destructor: libera todos los nodos
    ~ListLinked() {
        while (first != nullptr) {
            Node* temp = first;    // guardar nodo actual
            first = first->next;   // avanzar al siguiente
            delete temp;           // eliminar nodo anterior
        }
    }

    // insert: insertar e en posición pos (0 <= pos <= n)
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) throw std::out_of_range("insert: posición inválida");
        Node* nuevo = new Node(e);        // crear nodo nuevo
        if (pos == 0) {                   // insertar al principio
            nuevo->next = first;
            first = nuevo;
        } else {                          // insertar en medio o final
            Node* cur = first;
            for (int i = 0; i < pos - 1; ++i) cur = cur->next;
            nuevo->next = cur->next;
            cur->next = nuevo;
        }
        ++n;                              // actualizar contador
    }

    // append: añadir al final (reusa insert)
    void append(T e) override { insert(n, e); }

    // prepend: añadir al principio (reusa insert)
    void prepend(T e) override { insert(0, e); }

    // remove: eliminar y devolver elemento en pos (0 <= pos < n)
    T remove(int pos) override {
        if (pos < 0 || pos >= n) throw std::out_of_range("remove: posición inválida");
        Node* to_delete;
        T value;
        if (pos == 0) {                   // eliminar primer nodo
            to_delete = first;
            value = to_delete->data;
            first = first->next;
        } else {                          // eliminar nodo intermedio o final
            Node* cur = first;
            for (int i = 0; i < pos - 1; ++i) cur = cur->next;
            to_delete = cur->next;
            value = to_delete->data;
            cur->next = to_delete->next;
        }
        delete to_delete;                 // liberar nodo eliminado
        --n;                              // actualizar contador
        return value;                     // devolver valor eliminado
    }

    // acceso con corchetes (no const): devuelve referencia para poder modificar
    T& operator[](int pos) {
        if (pos < 0 || pos >= n) throw std::out_of_range("operator[]: fuera de rango");
        Node* cur = first;
        for (int i = 0; i < pos; ++i) cur = cur->next;
        return cur->data;
    }

    // acceso con corchetes const: devuelve referencia const
    const T& operator[](int pos) const {
        if (pos < 0 || pos >= n) throw std::out_of_range("operator[]: fuera de rango");
        Node* cur = first;
        for (int i = 0; i < pos; ++i) cur = cur->next;
        return cur->data;
    }

    // get: devolver copia del elemento en pos (comprobando rango)
    T get(int pos) const override {
        if (pos < 0 || pos >= n) throw std::out_of_range("get: posición inválida");
        Node* cur = first;
        for (int i = 0; i < pos; ++i) cur = cur->next;
        return cur->data;
    }

    // search: buscar primera ocurrencia de e, devolver índice o -1
    int search(T e) override {
        Node* cur = first;
        int idx = 0;
        while (cur != nullptr) {
            if (cur->data == e) return idx;
            cur = cur->next;
            ++idx;
        }
        return -1;
    }

    // empty: true si no hay elementos
    bool empty() override { return n == 0; }

    // size: número de elementos
    int size() const override { return n; }

    // impresión simple: [a, b, c]
    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        out << "[";                              // abrir corchetes
        Node* cur = list.first;                  // empezar desde el primer nodo
        while (cur != nullptr) {                 // mientras haya nodos
            out << cur->data;                    // imprimir el dato
            cur = cur->next;                     // avanzar al siguiente
            if (cur != nullptr) out << ", ";    // separar con coma si no es el último
        }
        out << "]";                              // cerrar corchetes
        return out;                              // devolver stream
    }
};

#endif // LISTLINKED_H