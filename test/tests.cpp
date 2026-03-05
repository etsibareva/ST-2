// Copyright 2025 UNN-CS Team
#include <gtest/gtest.h>
#include <cmath>
#include "circle.h"
#include "task.h"

const double PI_VAL = 3.14159265358979323846;
const double EPS_VAL = 1e-10;

TEST(CircleTest, ConstructorAndGettersWorksCorrect) {
  Circle circ(6.0);
  EXPECT_DOUBLE_EQ(circ.getRadius(), 6.0);
  EXPECT_DOUBLE_EQ(circ.getFerence(), 2 * PI_VAL * 6.0);
  EXPECT_DOUBLE_EQ(circ.getArea(), PI_VAL * 36.0);
}

TEST(CircleTest, SetFerenceUpdatesCorrect) {
  Circle circ(1.0);
  double newCircVal = 10.0;
  circ.setFerence(newCircVal);
  double expectR = newCircVal / (2 * PI_VAL);
  EXPECT_DOUBLE_EQ(circ.getFerence(), newCircVal);
  EXPECT_DOUBLE_EQ(circ.getRadius(), expectR);
  EXPECT_DOUBLE_EQ(circ.getArea(),
    PI_VAL * expectR * expectR);
}

TEST(CircleTest, SetAreaUpdatesCorrectly) {
  Circle circ(1.0);
  double newAreaVal = 50.0;
  circ.setArea(newAreaVal);
  double expectR = std::sqrt(newAreaVal / PI_VAL);
  EXPECT_NEAR(circ.getArea(), newAreaVal, 1e-10);
  EXPECT_NEAR(circ.getRadius(), expectR, 1e-10);
  EXPECT_NEAR(circ.getFerence(), 2 * PI_VAL * expectR, 1e-10);
}

TEST(CircleTest, ZeroRadiusAllowed) {
  Circle circ(0.0);
  EXPECT_DOUBLE_EQ(circ.getRadius(), 0.0);
  EXPECT_DOUBLE_EQ(circ.getFerence(), 0.0);
  EXPECT_DOUBLE_EQ(circ.getArea(), 0.0);
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

TEST(PoolCostTest, PositiveCostResult) {
  double totalCost = calculatePoolCost();
  EXPECT_GT(totalCost, 0.0);
}

TEST(CircleTest, FerenceToRadiusToAreaRecalculation) {
  Circle circ(1.0);
  double testFerence = 30.0;
  circ.setFerence(testFerence);

  double computedRadius = testFerence / (2 * PI_VAL);
  double computedArea = PI_VAL * computedRadius * computedRadius;

  EXPECT_NEAR(circ.getRadius(), computedRadius, EPS_VAL);
  EXPECT_NEAR(circ.getArea(), computedArea, EPS_VAL);
}

TEST(CircleTest, ConsistencyAfterAnotherRecalculation) {
  Circle circ(2.0);
  circ.setRadius(4.0);
  double radVal = circ.getRadius();
  double circVal = circ.getFerence();
  double areaVal = circ.getArea();

  circ.setFerence(circVal);
  EXPECT_NEAR(circ.getRadius(), radVal, EPS_VAL);
  EXPECT_NEAR(circ.getArea(), areaVal, EPS_VAL);

  circ.setArea(areaVal);
  EXPECT_NEAR(circ.getRadius(), radVal, EPS_VAL);
  EXPECT_NEAR(circ.getFerence(), circVal, EPS_VAL);
}

TEST(CircleTest, RecalculationTheOnes) {
  Circle circ(5.0);
  double origRadius = circ.getRadius();
  double origFerence = circ.getFerence();
  double origArea = circ.getArea();

  circ.setRadius(origRadius);
  EXPECT_DOUBLE_EQ(circ.getFerence(), origFerence);
  EXPECT_DOUBLE_EQ(circ.getArea(), origArea);

  circ.setFerence(origFerence);
  EXPECT_DOUBLE_EQ(circ.getRadius(), origRadius);
  EXPECT_DOUBLE_EQ(circ.getArea(), origArea);

  circ.setArea(origArea);
  EXPECT_DOUBLE_EQ(circ.getRadius(), origRadius);
  EXPECT_DOUBLE_EQ(circ.getFerence(), origFerence);
}

TEST(CircleTest, ZeroButPositiveRadius) {
  Circle circ(1e-10);
  EXPECT_GT(circ.getRadius(), 0.0);
  EXPECT_GT(circ.getFerence(), 0.0);
  EXPECT_GT(circ.getArea(), 0.0);
}

TEST(PoolCostTest, CostCalculationCorrect) {
  Circle inPool(3.0);
  Circle outPool(4.0);
  double expectPathArea = outPool.getArea()
    - inPool.getArea();
  double expectCost = expectPathArea * 1000.0
    + outPool.getFerence() * 2000.0;
  EXPECT_DOUBLE_EQ(calculatePoolCost(), expectCost);
}

TEST(PoolCostTest, PathAreaPositive) {
  Circle inPool(3.0);
  Circle outPool(4.0);
  EXPECT_GT(outPool.getArea() - inPool.getArea(), 0.0);
}

TEST(PoolCostTest, FenceLengthPositive) {
  Circle outPool(4.0);
  EXPECT_GT(outPool.getFerence(), 0.0);
}
