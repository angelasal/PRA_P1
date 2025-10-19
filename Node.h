#ifndef NODE_H
#define NODE_H

#include <ostream>

// Clase genérica Node<T> para listas enlazadas
template <typename T>
class Node {
public:
    T data;            // Dato almacenado
    Node<T>* next;     // Puntero al siguiente nodo

    // Constructor: inicializa el nodo con un dato y opcionalmente el siguiente nodo
    Node(T data, Node<T>* next = nullptr) : data(data), next(next) {}

    // Sobrecarga del operador << para imprimir el contenido del nodo
    friend std::ostream& operator<<(std::ostream& out, const Node<T>& node) {
        out << node.data;
        return out;
    }
};

#endif // NODE_H