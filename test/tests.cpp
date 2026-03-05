// Copyright 2025 UNN-CS Team
#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "task.h"

const double PI_VAL = 3.14159265358979323846;
const double EPS_VAL = 1e-10;

TEST(CircleTest, ConstructorAndGettersWorks) {
  Circle circ(5.0);
  EXPECT_DOUBLE_EQ(circ.getRadius(), 5.0);
  EXPECT_DOUBLE_EQ(circ.getFerence(), 2 * PI_VAL * 5.0);
  EXPECT_DOUBLE_EQ(circ.getArea(), PI_VAL * 25.0);
}

TEST(CircleTest, SetFerenceUpdatesCorrectly) {
  Circle circ(1.0);
  double newCircVal = 10.0;
  circ.setFerence(newCircVal);
  double expectRad = newCircVal / (2 * PI_VAL);
  EXPECT_DOUBLE_EQ(circ.getFerence(), newCircVal);
  EXPECT_DOUBLE_EQ(circ.getRadius(), expectRad);
  EXPECT_DOUBLE_EQ(circ.getArea(),
    PI_VAL * expectRad * expectRad);
}

TEST(CircleTest, SetAreaUpdatesCorrectly) {
  Circle circ(1.0);
  double newAreaVal = 50.0;
  circ.setArea(newAreaVal);
  double expectRad = std::sqrt(newAreaVal / PI_VAL);
  EXPECT_DOUBLE_EQ(circ.getArea(), newAreaVal);
  EXPECT_DOUBLE_EQ(circ.getRadius(), expectRad);
  EXPECT_DOUBLE_EQ(circ.getFerence(),
    2 * PI_VAL * expectRad);
}

TEST(CircleTest, ZeroRadiusAllowed) {
  Circle circ(0.0);
  EXPECT_DOUBLE_EQ(circ.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(circ.getFerence(), 0.0);
  EXPECT_DOUBLE_EQ(circ.getArea(), 0.0);
}

TEST(CircleTest, VerySmallRadiusWorks) {
  Circle circ(1e-10);
  EXPECT_NEAR(circ.getFerence(),
    2 * PI_VAL * 1e-10, EPS_VAL);
  EXPECT_NEAR(circ.getArea(),
    PI_VAL * 1e-20, EPS_VAL);
}

TEST(CircleTest, VeryLargeRadiusWorks) {
  Circle circ(1e10);
  EXPECT_DOUBLE_EQ(circ.getFerence(),
    2 * PI_VAL * 1e10);
  EXPECT_DOUBLE_EQ(circ.getArea(),
    PI_VAL * 1e20);
}

TEST(CircleTest, SetFerenceToZeroAllowed) {
  Circle circ(5.0);
  circ.setFerence(0.0);
  EXPECT_DOUBLE_EQ(circ.getFerence(), 0.0);
  EXPECT_DOUBLE_EQ(circ.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(circ.getArea(), 0.0);
}

TEST(CircleTest, SetAreaToZeroAllowed) {
  Circle circ(5.0);
  circ.setArea(0.0);
  EXPECT_DOUBLE_EQ(circ.getArea(), 0.0);
  EXPECT_DOUBLE_EQ(circ.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(circ.getFerence(), 0.0);
}

TEST(CircleTest, NegativeRadiusThrowsException) {
  Circle circ(1.0);
  EXPECT_THROW(circ.setRadius(-5.0),
    std::invalid_argument);
}

TEST(CircleTest, NegativeFerenceThrowsException) {
  Circle circ(1.0);
  EXPECT_THROW(circ.setFerence(-10.0),
    std::invalid_argument);
}

TEST(CircleTest, NegativeAreaThrowsException) {
  Circle circ(1.0);
  EXPECT_THROW(circ.setArea(-50.0),
    std::invalid_argument);
}

TEST(CircleTest, ConstructorNegativeThrowsException) {
  EXPECT_THROW(Circle circ(-5.0), std::invalid_argument);
}

TEST(CircleTest, ConsistencyAfterMultipleSets) {
  Circle circ(2.0);
  circ.setRadius(4.0);
  double radVal = circ.getRadius();
  double circVal = circ.getFerence();
  double areaVal = circ.getArea();

  circ.setFerence(circVal);
  EXPECT_DOUBLE_EQ(circ.getRadius(), radVal);
  EXPECT_DOUBLE_EQ(circ.getArea(), areaVal);

  circ.setArea(areaVal);
  EXPECT_DOUBLE_EQ(circ.getRadius(), radVal);
  EXPECT_DOUBLE_EQ(circ.getFerence(), circVal);
}

TEST(CircleTest, MathematicalRelationsHold) {
  Circle circ(7.0);
  EXPECT_DOUBLE_EQ(circ.getFerence(),
    2 * PI_VAL * circ.getRadius());
  EXPECT_DOUBLE_EQ(circ.getArea(),
    PI_VAL * circ.getRadius() * circ.getRadius());
}

TEST(EarthGapTest, PositiveGapResult) {
  double gapResult = calculateEarthGap();
  EXPECT_GT(gapResult, 0.0);
}

TEST(EarthGapTest, GapValueCorrect) {
  double gapResult = calculateEarthGap();
  double expectGap = 1.0 / (2 * PI_VAL);
  EXPECT_NEAR(gapResult, expectGap, EPS_VAL);
}

TEST(EarthGapTest, GapIndependentFromRadius) {
  double firstGap = calculateEarthGap();
  double secondGap = calculateEarthGap();
  EXPECT_DOUBLE_EQ(firstGap, secondGap);
}

TEST(PoolCostTest, PositiveCostResult) {
  double totalCost = calculatePoolCost();
  EXPECT_GT(totalCost, 0.0);
}

TEST(PoolCostTest, ConcreteAreaCalculation) {
  Circle innerPool(3.0);
  Circle outerPool(4.0);
  double expectPathArea = outerPool.getArea()
    - innerPool.getArea();
  double expectCost = expectPathArea * 1000.0
    + outerPool.getFerence() * 2000.0;
  EXPECT_DOUBLE_EQ(calculatePoolCost(), expectCost);
}

TEST(PoolCostTest, CostBreakdownCheck) {
  Circle innerPool(3.0);
  Circle outerPool(4.0);
  double pathAreaVal = outerPool.getArea()
    - innerPool.getArea();
  double concreteCostVal = pathAreaVal * 1000.0;
  double fenceCostVal = outerPool.getFerence() * 2000.0;
  double totalCostVal = concreteCostVal + fenceCostVal;
  EXPECT_DOUBLE_EQ(calculatePoolCost(), totalCostVal);
}

TEST(PoolCostTest, PathAreaPositive) {
  Circle innerPool(3.0);
  Circle outerPool(4.0);
  EXPECT_GT(outerPool.getArea() - innerPool.getArea(), 0.0);
}

TEST(PoolCostTest, FenceLengthPositive) {
  Circle outerPool(4.0);
  EXPECT_GT(outerPool.getFerence(), 0.0);
}
