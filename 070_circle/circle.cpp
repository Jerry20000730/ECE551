#include <cstdio>
#include <cmath>
#include <algorithm>

#include "circle.hpp"

Circle::Circle(const Point & p, const double r) : center(p), radius(r) {}

void Circle::move(double dx, double dy) {
    center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
    double distance = center.distanceFrom(otherCircle.center);
    if (distance >= this->radius + otherCircle.radius) {
        return 0;
    }

    if (distance <= std::abs(radius - otherCircle.radius)) {
        double smallerCircleArea = M_PI * std::min(radius, otherCircle.radius) * std::min(radius, otherCircle.radius);
        return smallerCircleArea;
    }

    // Compute the area of intersection using the formula for intersecting circles
    double d = distance;
    double r = radius;
    double R = otherCircle.radius;
    double part1 = r * r * acos((d * d + r * r - R * R) / (2 * d * r));
    double part2 = R * R * acos((d * d + R * R - r * r) / (2 * d * R));
    double part3 = 0.5 * sqrt((-d + r + R) * (d + r - R) * (d - r + R) * (d + r + R));
    double intersectionArea = part1 + part2 - part3;
    return intersectionArea;
}