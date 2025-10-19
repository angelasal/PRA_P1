#ifndef LISTARRAY_H
#define LISTARRAY_H

#include "List.h"      // Incluimos la interfaz List<T>
#include <stdexcept>   // Para lanzar excepciones std::out_of_range


// Clase genérica que implementa una lista usando un array dinámico
template <typename T>
class ListArray : public List<T> {
private:
    T* data;           // Puntero al array dinámico
    int capacity;      // Capacidad total del array
    int count;         // Número actual de elementos

    // Método privado para redimensionar el array cuando se llena
    void resize(int new_capacity) {
        T* new_data = new T[new_capacity]; // Crear nuevo array
        for (int i = 0; i < count; ++i) {
            new_data[i] = data[i];         // Copiar elementos
        }
        delete[] data;                     // Liberar memoria anterior
        data = new_data;                   // Actualizar puntero
        capacity = new_capacity;          // Actualizar capacidad
    }

public:
    // Constructor: inicializa el array con capacidad inicial
    ListArray(int init_capacity = 10) {
        data = new T[init_capacity];
        capacity = init_capacity;
        count = 0;
    }

    // Destructor: libera la memoria del array
    ~ListArray() {
        delete[] data;
    }

    // Inserta el elemento e en la posición pos
    void insert(int pos, T e) override {
        if (pos < 0 || pos > count) {
            throw std::out_of_range("Posición inválida en insert()");
        }
        if (count == capacity) {
            resize(capacity * 2); // Duplicar capacidad si está lleno
        }
        for (int i = count; i > pos; --i) {
            data[i] = data[i - 1]; // Desplazar elementos hacia la derecha
        }
        data[pos] = e; // Insertar el nuevo elemento
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
        T removed = data[pos]; // Guardar el elemento a eliminar
        for (int i = pos; i < count - 1; ++i) {
            data[i] = data[i + 1]; // Desplazar elementos hacia la izquierda
        }
        --count;
        return removed;
    }

    // Devuelve el elemento en la posición pos
    T get(int pos) override {
        if (pos < 0 || pos >= count) {
            throw std::out_of_range("Posición inválida en get()");
        }
        return data[pos];
    }

    // Busca la primera ocurrencia del elemento e
    int search(T e) override {
        for (int i = 0; i < count; ++i) {
            if (data[i] == e) {
                return i; // Retorna la posición si lo encuentra
            }
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

#endif // LISTARRAY_H