#include <UniSlefe.hpp>
#include <UniSlefeBuilder.hpp>

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using UniSlefeBuilder = slefe::UniSlefeBuilder;

namespace {
// Tolerance adopted by floating-point number comparisons.
constexpr static auto EqualityTolerance = 1e-8;

// Control values of univariate Bézier functions of degree 2 thru 9.
const static std::vector<std::vector<double>> ControlValues = {
    {0.0, 1.0, 0.8},                                    // degree 2
    {0.0, 1.0, 0.8, -0.2},                              // degree 3
    {0.0, 1.0, 0.8, -0.2, 2.5},                         // degree 4
    {0.0, 1.0, 0.8, -0.2, 2.5, 3.5},                    // degree 5
    {0.0, 1.0, 0.8, -0.2, 2.5, 3.5, 2.0},               // degree 6
    {0.0, 1.0, 0.8, -0.2, 2.5, 3.5, 2.0, 5.2},          // degree 7
    {0.0, 1.0, 0.8, -0.2, 2.5, 3.5, 2.0, 5.2, 4.0},     // degree 8
    {0.0, 1.0, 0.8, -0.2, 2.5, 3.5, 2.0, 5.2, 4.0, 0.5} // degree 9
};

// Evaluates all Bernstein basis functions of a given degree at a given point.
std::vector<double> evaluateBernsteinBasisFunctions(int n, double t) {
  std::vector<double> bfValues(n + 1, 0.0);

  const auto u = 1.0 - t;
  bfValues[0] = 1.0;
  for (auto ii = 1; ii <= n; ++ii) {
    auto result = 0.0;

    for (auto jj = 0; jj < ii; ++jj) {
      const auto temp = bfValues[jj];
      bfValues[jj] = result + u * temp;
      result = t * temp;
    }

    bfValues[ii] = result;
  }

  return bfValues;
}

// Returns the value of a univariate Bézier polynomial of a given degree at a
// given parameter value.
double evaluateBezierFunctionAt(const std::vector<double> &controlValues,
                                int degree, double t) {
  if (degree <= 0) {
    throw std::invalid_argument(
        "The degree of the polynomial function must be at least 1.");
  }

  if (t < 0.0 || t > 1.0) {
    throw std::invalid_argument("The parameter value must be a number in the "
                                "real line interval [0,1].");
  }

  const auto numberOfControlValues = static_cast<int>(controlValues.size());
  if (degree + 1 != numberOfControlValues) {
    throw std::invalid_argument("The degree and number of control values are "
                                "inconsistent with each other.");
  }

  const auto bbfValues = evaluateBernsteinBasisFunctions(degree, t);
  const auto numberOfBasisFunctionValues = static_cast<int>(bbfValues.size());
  if (numberOfControlValues != numberOfBasisFunctionValues) {
    throw std::runtime_error("The number of Bernstein basis functions must "
                             "match the number of control values.");
  }

  auto sum = 0.0;
  for (auto idx = 0; idx < numberOfControlValues; ++idx) {
    sum += bbfValues[idx] * controlValues[idx];
  }

  return sum;
}

// Checks whether the lower and upper components of a slefe are consistent with
// each other.
void checkConsistencyOfLowerAndUpperComponents(int degree) {
  ASSERT_GE(degree, 2);

  const auto &coeffs = ControlValues[degree - 2];
  UniSlefeBuilder builder;
  for (auto segments = 1; segments <= UniSlefeBuilder::MaximumNumberOfSegments;
       ++segments) {
    const auto slefe = builder.build(degree, segments, coeffs);

    const auto &lowerValues = slefe.lowerValues();
    const auto &upperValues = slefe.upperValues();

    const auto numberOfValues = static_cast<int>(upperValues.size());

    ASSERT_EQ(numberOfValues, segments + 1);
    ASSERT_EQ(numberOfValues, static_cast<int>(lowerValues.size()));

    for (auto idx = 0; idx < segments; ++idx) {
      EXPECT_LE(lowerValues[idx], upperValues[idx]);
    }
  }
}

// Checks whether the lower and upper bounds of a slefe at breakpoints are
// correct.
void checkValuesAtBreakpoints(int degree) {
  ASSERT_GE(degree, 2);
  ASSERT_LE(degree, UniSlefeBuilder::MaximumDegree);

  const auto &coeffs = ControlValues[degree - 2];
  UniSlefeBuilder builder;
  for (auto segments = 1; segments <= UniSlefeBuilder::MaximumNumberOfSegments;
       ++segments) {
    const auto slefe = builder.build(degree, segments, coeffs);

    const auto &lowerValues = slefe.lowerValues();
    const auto &upperValues = slefe.upperValues();

    for (auto idx = 0; idx <= segments; ++idx) {
      const auto t = std::clamp(static_cast<double>(idx) / segments, 0.0, 1.0);

      const auto lowerValue = slefe.lowerValueAt(t);
      const auto upperValue = slefe.upperValueAt(t);

      EXPECT_NEAR(lowerValue, lowerValues[idx], EqualityTolerance);
      EXPECT_NEAR(upperValue, upperValues[idx], EqualityTolerance);
    }
  }
}

// Checks whether the graph of a Bézier function is enclosed by its slefe.
void checkFunctionEnclosure(int degree) {
  constexpr auto NumberOfSamples = 10000;

  ASSERT_GE(degree, 2);
  ASSERT_LE(degree, UniSlefeBuilder::MaximumDegree);

  const auto &coeffs = ControlValues[degree - 2];
  UniSlefeBuilder builder;
  for (auto segments = 1; segments <= UniSlefeBuilder::MaximumNumberOfSegments;
       ++segments) {
    const auto slefe = builder.build(degree, segments, coeffs);

    for (auto idx = 0; idx <= NumberOfSamples; ++idx) {
      double t = static_cast<double>(idx) / NumberOfSamples;

      const auto lowerValue = slefe.lowerValueAt(t);
      const auto upperValue = slefe.upperValueAt(t);
      const auto functValue = evaluateBezierFunctionAt(coeffs, degree, t);

      if (lowerValue > functValue) {
        EXPECT_NEAR(lowerValue, functValue, EqualityTolerance);
      }

      if (upperValue < functValue) {
        EXPECT_NEAR(upperValue, functValue, EqualityTolerance);
      }
    }
  }
}
} // namespace

TEST(SLEFE, Consistency) {
  const auto numberOfControlValues = static_cast<int>(ControlValues.size());
  for (auto degree = 2; degree <= numberOfControlValues; ++degree) {
    checkConsistencyOfLowerAndUpperComponents(degree);
  }
}

TEST(SLEFE, Breakpoints) {
  const auto numberOfControlValues = static_cast<int>(ControlValues.size());
  for (auto degree = 2; degree <= numberOfControlValues; ++degree) {
    checkValuesAtBreakpoints(degree);
  }
}

TEST(SLEFE, Enclosure) {
  const auto numberOfControlValues = static_cast<int>(ControlValues.size());
  for (auto degree = 2; degree <= numberOfControlValues; ++degree) {
    checkFunctionEnclosure(degree);
  }
}
