#ifndef LISTARRAY_H
#define LISTARRAY_H

#include <stdexcept> // para lanzar std::out_of_range
#include <ostream>   // para declarar operator<<

template<typename T>               // clase genérica parametrizada por T
class ListArray {
private:
    T* arr;                       // puntero al inicio del array dinámico
    int max;                      // capacidad actual (cuántos caben)
    int n;                        // número de elementos almacenados
    static const int MINSIZE = 2; // tamaño mínimo del array (=2)

    // redimensiona el array a new_size siguiendo los pasos pedidos
    void resize(int new_size) {
        if (new_size < MINSIZE) new_size = MINSIZE;   // 1) no permitir < MINSIZE
        T* new_arr = new T[new_size];                 // 2) crear nuevo array con new_size
        for (int i = 0; i < n; ++i)                   // 3) copiar los n elementos válidos
            new_arr[i] = arr[i];
        delete[] arr;                                 // 4) liberar memoria del array viejo
        arr = new_arr;                                // 5) actualizar puntero arr
        max = new_size;                               // 6) actualizar capacidad max
    }

public:
    // constructor sin argumentos: reserva MINSIZE elementos
    ListArray() {
        arr = new T[MINSIZE]; // reservar memoria para MINSIZE elementos
        max = MINSIZE;        // establecer capacidad inicial
        n = 0;                // empezar con 0 elementos
    }

    // constructor con capacidad inicial (opcional, mínima MINSIZE)
    ListArray(int init_capacity) {
        if (init_capacity < MINSIZE) init_capacity = MINSIZE; // asegurar mínimo
        arr = new T[init_capacity]; // reservar memoria
        max = init_capacity;        // fijar capacidad
        n = 0;                      // lista vacía inicialmente
    }

    // buscar primera ocurrencia de e, devolver índice o -1
    int search(T e) {
        for (int i = 0; i < n; ++i) {           // recorrer elementos
            if (arr[i] == e) return i;          // si coincide, devolver índice
        }
        return -1;                              // si no encuentra, devolver -1
    }

    // destructor: libera la memoria dinámica reservada
    ~ListArray() {
        delete[] arr; // liberar array al destruir el objeto
    }

    // inserta e en la posición pos (0 <= pos <= n)
    void insert(int pos, T e) {
        if (pos < 0 || pos > n)                            // validar posición
            throw std::out_of_range("insert: posición inválida");
        if (n == max) resize(max * 2);                     // ampliar si está lleno
        for (int i = n; i > pos; --i)                      // desplazar elementos a la derecha
            arr[i] = arr[i - 1];
        arr[pos] = e;                                      // colocar el nuevo elemento
        ++n;                                               // aumentar contador de elementos
    }

    // añade e al final de la lista
    void append(T e) {
        insert(n, e); // reutiliza insert para evitar duplicar código
    }

    // añade e al principio de la lista
    void prepend(T e) {
        insert(0, e); // reutiliza insert para insertar en la posición 0
    }

    // elimina y devuelve el elemento en pos (0 <= pos < n)
    T remove(int pos) {
        if (pos < 0 || pos >= n)                           // validar posición
            throw std::out_of_range("remove: posición inválida");
        T value = arr[pos];                                // guardar valor a devolver
        for (int i = pos; i < n - 1; ++i)                  // desplazar elementos a la izquierda
            arr[i] = arr[i + 1];
        --n;                                               // disminuir contador
        // reducir tamaño si está demasiado vacío (umbral: 1/4) y no bajar de MINSIZE
        if (n <= max / 4 && max / 2 >= MINSIZE) resize(max / 2);
        return value;                                      // devolver elemento eliminado
    }

    // acceso con corchetes (no const): devuelve referencia para poder modificar
    T& operator[](int pos) {
        if (pos < 0 || pos >= n)                          // comprobar rango
            throw std::out_of_range("operator[]: fuera de rango");
        return arr[pos];                                  // devolver referencia al elemento
    }

    // obtiene copia del elemento en pos (comprobando rango)
    T get(int pos) const {
        if (pos < 0 || pos >= n)
            throw std::out_of_range("get: fuera de rango");
        return arr[pos];                                  // devolver copia
    }

    // número de elementos almacenados
    int size() const { return n; }

    // indica si la lista está vacía
    bool empty() const { return n == 0; }

    // impresión simple: [a, b, c]
    friend std::ostream& operator<<(std::ostream& out, const ListArray<T>& list) {
        out << "[";                                      // abrir corchetes
        for (int i = 0; i < list.n; ++i) {               // recorrer elementos
            out << list.arr[i];                          // imprimir elemento
            if (i + 1 < list.n) out << ", ";            // separar con coma si no es el último
        }
        out << "]";                                      // cerrar corchetes
        return out;                                      // devolver stream
    }
};

#endif // LISTARRAY_H
