#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */

Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

double Vector2D::getMagnitude() const {
    return std::sqrt(std::pow(x, 2)+std::pow(y, 2));
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
    Vector2D res(x + rhs.x, y + rhs.y);
    return res;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
    return x * rhs.x + y * rhs.y;
}

void Vector2D::print() const {
    printf("<%.2f, %.2f>", x, y);
}
