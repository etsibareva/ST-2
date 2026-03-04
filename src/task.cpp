// Copyright 2022 UNN-CS
#include <cmath>
#include "circle.h"
#include "task.h"

double calculateEarthGap() {
    double earthRadius = 6378100.0; // 6378.1 km in meters
    Circle earth(earthRadius);
    double oldFerence = earth.getFerence();
    double newFerence = oldFerence + 1.0;
    earth.setFerence(newFerence);
    return earth.getRadius() - earthRadius;
}

double calculatePoolCost() {
    double poolRadius = 3.0;
    double pathWidth = 1.0;
    
    Circle pool(poolRadius);
    Circle poolWithPath(poolRadius + pathWidth);
    
    double pathArea = poolWithPath.getArea() - pool.getArea();
    double concreteCost = pathArea * 1000.0;
    
    double fenceLength = poolWithPath.getFerence();
    double fenceCost = fenceLength * 2000.0;
    
    return concreteCost + fenceCost;
}
