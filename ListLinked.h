#ifndef LISTLINKED_H
#define LISTLINKED_H

#include "List.h"        // Incluimos la interfaz List<T>
#include <stdexcept>     // Para lanzar excepciones std::out_of_range

// Clase genérica que implementa una lista enlazada simple
template <typename T>
class ListLinked : public List<T> {
private:
    // Estructura interna para representar cada nodo de la lista
    struct Node {
        T data;          // Dato almacenado
        Node* next;      // Puntero al siguiente nodo

        Node(T d) : data(d), next(nullptr) {} // Constructor del nodo
    };

    Node* head;          // Puntero al primer nodo
    int count;           // Número de elementos en la lista

public:
    // Constructor: inicializa la lista vacía
    ListLinked() : head(nullptr), count(0) {}

    // Destructor: libera todos los nodos
    ~ListLinked() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Inserta el elemento e en la posición pos
    void insert(int pos, T e) override {
        if (pos < 0 || pos > count) {
            throw std::out_of_range("Posición inválida en insert()");
        }

        Node* new_node = new Node(e); // Crear nuevo nodo

        if (pos == 0) {
            // Insertar al principio
            new_node->next = head;
            head = new_node;
        } else {
            // Insertar en posición intermedia o final
            Node* current = head;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }

        ++count;
    }

    // Inserta al final (reutiliza insert)
    void append(T e) override {
        insert(count, e); // Insertar en la última posición
    }

    // Inserta al principio (reutiliza insert)
    void prepend(T e) override {
        insert(0, e); // Insertar en la posición 0
    }

    // Elimina y devuelve el elemento en la posición pos
    T remove(int pos) override {
        if (pos < 0 || pos >= count) {
            throw std::out_of_range("Posición inválida en remove()");
        }

        Node* to_delete;
        T value;

        if (pos == 0) {
            // Eliminar el primer nodo
            to_delete = head;
            value = to_delete->data;
            head = head->next;
        } else {
            // Eliminar nodo intermedio o final
            Node* current = head;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            to_delete = current->next;
            value = to_delete->data;
            current->next = to_delete->next;
        }

        delete to_delete;
        --count;
        return value;
    }

    // Devuelve el elemento en la posición pos
    T get(int pos) override {
        if (pos < 0 || pos >= count) {
            throw std::out_of_range("Posición inválida en get()");
        }

        Node* current = head;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }

        return current->data;
    }

    // Busca la primera ocurrencia del elemento e
    int search(T e) override {
        Node* current = head;
        int index = 0;

        while (current != nullptr) {
            if (current->data == e) {
                return index;
            }
            current = current->next;
            ++index;
        }

        return -1; // No encontrado
    }

    // Indica si la lista está vacía
    bool empty() override {
        return count == 0;
    }

    // Devuelve el número de elementos
    int size() override {
        return count;
    }
};

#endif // LISTLINKED_H