#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include<cstdio>

#include "point.hpp"

class Circle {
private:
    Point center;
    const double radius;
public:
    Circle(const Point & p, const double r);
    void move (double dx, double dy);
    double intersectionArea(const Circle & otherCircle);
};

#endif