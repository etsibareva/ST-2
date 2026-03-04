// Copyright 2025 UNN-CS Team
#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "task.h"

const double PI = 3.14159265358979323846;
const double EPS = 1e-10;

TEST(CircleTest, ConstructorAndGetters) {
    Circle c(5.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 5.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * 5.0);
    EXPECT_DOUBLE_EQ(c.getArea(), PI * 25.0);
}

TEST(CircleTest, SetFerence) {
    Circle c(1.0);
    double newFerence = 10.0;
    c.setFerence(newFerence);
    double expectedRadius = newFerence / (2 * PI);
    EXPECT_DOUBLE_EQ(c.getFerence(), newFerence);
    EXPECT_DOUBLE_EQ(c.getRadius(), expectedRadius);
    EXPECT_DOUBLE_EQ(c.getArea(), PI * expectedRadius * expectedRadius);
}

TEST(CircleTest, SetArea) {
    Circle c(1.0);
    double newArea = 50.0;
    c.setArea(newArea);
    double expectedRadius = std::sqrt(newArea / PI);
    EXPECT_DOUBLE_EQ(c.getArea(), newArea);
    EXPECT_DOUBLE_EQ(c.getRadius(), expectedRadius);
    EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * expectedRadius);
}

TEST(CircleTest, ZeroRadius) {
    Circle c(0.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
    EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, NegativeRadius) {
    Circle c(-5.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * (-5.0));
    EXPECT_DOUBLE_EQ(c.getArea(), PI * 25.0);
}

TEST(CircleTest, VerySmallRadius) {
    Circle c(1e-10);
    EXPECT_NEAR(c.getFerence(), 2 * PI * 1e-10, EPS);
    EXPECT_NEAR(c.getArea(), PI * 1e-20, EPS);
}

TEST(CircleTest, VeryLargeRadius) {
    Circle c(1e10);
    EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * 1e10);
    EXPECT_DOUBLE_EQ(c.getArea(), PI * 1e20);
}

TEST(CircleTest, SetFerenceZero) {
    Circle c(5.0);
    c.setFerence(0.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
    EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
}

TEST(CircleTest, SetAreaZero) {
    Circle c(5.0);
    c.setArea(0.0);
    EXPECT_DOUBLE_EQ(c.getArea(), 0.0);
    EXPECT_DOUBLE_EQ(c.getRadius(), 0.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 0.0);
}

TEST(CircleTest, ConsistencyAfterMultipleSets) {
    Circle c(2.0);
    c.setRadius(4.0);
    double r1 = c.getRadius();
    double f1 = c.getFerence();
    double a1 = c.getArea();
    
    c.setFerence(f1);
    EXPECT_DOUBLE_EQ(c.getRadius(), r1);
    EXPECT_DOUBLE_EQ(c.getArea(), a1);
    
    c.setArea(a1);
    EXPECT_DOUBLE_EQ(c.getRadius(), r1);
    EXPECT_DOUBLE_EQ(c.getFerence(), f1);
}

TEST(CircleTest, MathematicalRelations) {
    Circle c(7.0);
    EXPECT_DOUBLE_EQ(c.getFerence(), 2 * PI * c.getRadius());
    EXPECT_DOUBLE_EQ(c.getArea(), PI * c.getRadius() * c.getRadius());
}

TEST(EarthGapTest, PositiveGap) {
    double gap = calculateEarthGap();
    EXPECT_GT(gap, 0.0);
}

TEST(EarthGapTest, GapValue) {
    double gap = calculateEarthGap();
    double expectedGap = 1.0 / (2 * PI);
    EXPECT_NEAR(gap, expectedGap, 1e-10);
}

TEST(EarthGapTest, GapIndependenceFromRadius) {
    double gap1 = calculateEarthGap();
    double gap2 = calculateEarthGap();
    EXPECT_DOUBLE_EQ(gap1, gap2);
}

TEST(PoolCostTest, PositiveCost) {
    double cost = calculatePoolCost();
    EXPECT_GT(cost, 0.0);
}

TEST(PoolCostTest, ConcreteArea) {
    Circle pool(3.0);
    Circle poolWithPath(4.0);
    double expectedPathArea = poolWithPath.getArea() - pool.getArea();
    double expectedCost = expectedPathArea * 1000.0 + poolWithPath.getFerence() * 2000.0;
    EXPECT_DOUBLE_EQ(calculatePoolCost(), expectedCost);
}

TEST(PoolCostTest, CostBreakdown) {
    Circle pool(3.0);
    Circle poolWithPath(4.0);
    double pathArea = poolWithPath.getArea() - pool.getArea();
    double concreteCost = pathArea * 1000.0;
    double fenceCost = poolWithPath.getFerence() * 2000.0;
    double totalCost = concreteCost + fenceCost;
    EXPECT_DOUBLE_EQ(calculatePoolCost(), totalCost);
}

TEST(PoolCostTest, PathAreaPositive) {
    Circle pool(3.0);
    Circle poolWithPath(4.0);
    EXPECT_GT(poolWithPath.getArea() - pool.getArea(), 0.0);
}

TEST(PoolCostTest, FenceLengthPositive) {
    Circle poolWithPath(4.0);
    EXPECT_GT(poolWithPath.getFerence(), 0.0);
}
