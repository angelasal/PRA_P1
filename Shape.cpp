#include "Shape.h"

// Constructor por defecto
Shape::Shape() : color("red") {}

// Constructor con validación
Shape::Shape(std::string color) {
    if (!is_valid_color(color)) {
        throw std::invalid_argument("Color inválido: " + color);
    }
    this->color = color;
}

// Getter
std::string Shape::get_color() const {
    return color;
}

// Setter con validación
void Shape::set_color(std::string c) {
    if (!is_valid_color(c)) {
        throw std::invalid_argument("Color inválido: " + c);
    }
    color = c;
}