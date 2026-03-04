// Copyright 2022 UNN-CS
#define _USE_MATH_DEFINES
#include <cmath>
#include "circle.h"

Circle::Circle(double r) {
    setRadius(r);
    
}

void Circle::setRadius(double r) {
    radius = r;
    ference = 2 * M_PI * radius;
    area = M_PI * radius * radius;
}

void Circle::setFerence(double f) {
    ference = f;
    radius = ference / (2 * M_PI);
    area = M_PI * radius * radius;
}

void Circle::setArea(double a) {
    area = a;
    radius = std::sqrt(area / M_PI);
    ference = 2 * M_PI * radius;
}

double Circle::getRadius() const {
    return radius;
}

double Circle::getFerence() const {
    return ference;
}

double Circle::getArea() const {
    return area;
}
