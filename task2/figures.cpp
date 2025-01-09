#include "figures.hpp"
#include <cmath>

Rect::Rect(double width, double height) : width(width), height(height) {
    if (width < 0 || height < 0) {
        throw LessThanZeroParam();
    }
}

FigureType Rect::Type() const {
    return FigureType::RECTANGLE;
}

double Rect::Perimeter() const {
    return 2 * (width + height);
}

double Rect::Area() const {
    return width * height;
}

Triangle::Triangle(double a, double b, double c) : a(a), b(b), c(c) {
    if (a < 0 || b < 0 || c < 0) {
        throw LessThanZeroParam();
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        throw WrongTriangle();
    }
}

FigureType Triangle::Type() const {
    return FigureType::TRIANGLE;
}

double Triangle::Perimeter() const {
    return a + b + c;
}

double Triangle::Area() const {
    double p = Perimeter() / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

Circle::Circle(double radius) : radius(radius) {
    if (radius < 0) {
        throw LessThanZeroParam();
    }
}

FigureType Circle::Type() const {
    return FigureType::CIRCLE;
}

double Circle::Perimeter() const {
    return 2 * PI * radius;
}

double Circle::Area() const {
    return PI * radius * radius;
}

std::unique_ptr<Figure> make_figure(FigureType type, double a, double b = -1, double c = -1) {
    switch (type) {
        case FigureType::RECTANGLE:
            if (a <= 0 || b <= 0) throw LessThanZeroParam();
            return std::make_unique<Rect>(a, b);
        case FigureType::CIRCLE:
            if (a <= 0) throw LessThanZeroParam();
            return std::make_unique<Circle>(a);
        case FigureType::TRIANGLE:
            if (a <= 0 || b <= 0 || c <= 0) throw LessThanZeroParam();
            return std::make_unique<Triangle>(a, b, c);
        default:
            throw std::invalid_argument("Invalid figure type");
    }
}

