#ifndef LISTLINKED_H
#define LISTLINKED_H

#include "List.h"        // interfaz List<T>
#include <stdexcept>     // para std::out_of_range
#include <ostream>       // (opcional) si se quiere imprimir con operator<<

template<typename T>
class ListLinked : public List<T> {
private:
    struct Node {          // nodo interno sencillo
        T data;            // dato almacenado
        Node* next;        // puntero al siguiente nodo
        Node(T d) : data(d), next(nullptr) {} // constructor del nodo
    };

    Node* head;            // puntero al primer nodo
    int count;             // número de elementos

public:
    // constructor: lista vacía
    ListLinked() : head(nullptr), count(0) {}

    // destructor: libera todos los nodos
    ~ListLinked() {
        while (head != nullptr) {
            Node* temp = head;    // guardar nodo actual
            head = head->next;    // avanzar al siguiente
            delete temp;          // eliminar nodo anterior
        }
    }

    // insert: insertar e en posición pos (0 <= pos <= count)
    void insert(int pos, T e) override {
        if (pos < 0 || pos > count) throw std::out_of_range("insert: posición inválida");
        Node* nuevo = new Node(e);        // crear nodo nuevo
        if (pos == 0) {                   // insertar al principio
            nuevo->next = head;
            head = nuevo;
        } else {                          // insertar en medio o final
            Node* cur = head;
            for (int i = 0; i < pos - 1; ++i) cur = cur->next;
            nuevo->next = cur->next;
            cur->next = nuevo;
        }
        ++count;                          // actualizar contador
    }

    // append: añadir al final (reusa insert)
    void append(T e) override { insert(count, e); }

    // prepend: añadir al principio (reusa insert)
    void prepend(T e) override { insert(0, e); }

    // remove: eliminar y devolver elemento en pos (0 <= pos < count)
    T remove(int pos) override {
        if (pos < 0 || pos >= count) throw std::out_of_range("remove: posición inválida");
        Node* to_delete;
        T value;
        if (pos == 0) {                   // eliminar primer nodo
            to_delete = head;
            value = to_delete->data;
            head = head->next;
        } else {                          // eliminar nodo intermedio o final
            Node* cur = head;
            for (int i = 0; i < pos - 1; ++i) cur = cur->next;
            to_delete = cur->next;
            value = to_delete->data;
            cur->next = to_delete->next;
        }
        delete to_delete;                 // liberar nodo eliminado
        --count;                          // actualizar contador
        return value;                     // devolver valor eliminado
    }

    // get: devolver copia del elemento en pos (comprobando rango)
    T get(int pos) const override {
        if (pos < 0 || pos >= count) throw std::out_of_range("get: posición inválida");
        Node* cur = head;
        for (int i = 0; i < pos; ++i) cur = cur->next;
        return cur->data;
    }

    // search: buscar primera ocurrencia de e, devolver índice o -1
    int search(T e) override {
        Node* cur = head;
        int idx = 0;
        while (cur != nullptr) {
            if (cur->data == e) return idx;
            cur = cur->next;
            ++idx;
        }
        return -1;
    }

    // empty: true si no hay elementos
    bool empty() override { return count == 0; }

    // size: número de elementos
    int size() const override { return count; }
};

#endif // LISTLINKED_H