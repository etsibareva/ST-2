// Copyright 2022 UNN-CS
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>
#include "circle.h"

Circle::Circle(double r) {
  setRadius(r);
}

void Circle::setRadius(double r) {
  if (r < 0.0) {
    throw std::invalid_argument("Radius cannot be negative");
  }
  radius = r;
  ference = 2 * M_PI * radius;
  area = M_PI * radius * radius;
}

void Circle::setFerence(double f) {
  if (f < 0.0) {
    throw std::invalid_argument("Circumference cannot be negative");
  }
  ference = f;
  radius = ference / (2 * M_PI);
  area = M_PI * radius * radius;
}

void Circle::setArea(double a) {
  if (a < 0.0) {
    throw std::invalid_argument("Area cannot be negative");
  }
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
