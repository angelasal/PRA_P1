#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <stdexcept>
#include "Point2D.h"

class Shape {
protected:
    std::string color;

    bool is_valid_color(const std::string& c) const {
        return c == "red" || c == "green" || c == "blue";
    }

public:
    Shape(); // Constructor por defecto
    Shape(std::string color); // Constructor con color

    std::string get_color() const;
    void set_color(std::string c);

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void translate(double incX, double incY) = 0;
    virtual void print() = 0;

    virtual ~Shape() = default; // Destructor virtual
};

#endif