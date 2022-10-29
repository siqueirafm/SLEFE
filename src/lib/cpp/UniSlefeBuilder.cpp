#include "UniSlefeBuilder.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>

namespace slefe {
UniSlefe UniSlefeBuilder::build(int degree, int numberOfSegments,
                                const std::vector<double> &coeffs) const {
  if (degree < 2 || degree > MaximumDegree) {
    throw std::invalid_argument("The degree of the univariate function "
                                "must be at least 2 and no more than " +
                                std::to_string(MaximumDegree));
  }

  if (numberOfSegments < 1 || numberOfSegments > MaximumNumberOfSegments) {
    throw std::invalid_argument("The number of pieces of the slefe must be "
                                "greater than 0 and no more than " +
                                std::to_string(MaximumNumberOfSegments));
  }

  if (coeffs.size() != size_t(degree + 1)) {
    throw std::runtime_error("The number of coefficients and the degree "
                             "are inconsistent with each other");
  }

  // Compute the 2nd differences of the coefficients of the input function.
  const auto numberOfBasisFunctions = degree - 1;
  std::vector<double> secondDiffs(numberOfBasisFunctions);
  for (auto idx = 0; idx < numberOfBasisFunctions; ++idx) {
    secondDiffs[idx] = coeffs[idx] - 2.0 * coeffs[idx + 1] + coeffs[idx + 2];
  }

  // Save the left and right most coefficients.
  const auto lCoeff = coeffs[0];
  const auto rCoeff = coeffs[degree];

  // Compute the values of the lower and upper slefe components at the
  // breakpoints.
  std::vector<double> lowerValues(numberOfSegments + 1);
  std::vector<double> upperValues(numberOfSegments + 1);

  const auto numberOfCoefficients = numberOfSegments + 1;
  const auto degIdx = degree - 2;

  // Select pre-tabulated lower and upper bounds for the given degree and
  // number of segments.
  const auto &lowerBounds = LowerBounds[degIdx][numberOfSegments - 1];
  const auto &upperBounds = UpperBounds[degIdx][numberOfSegments - 1];

  // Compute a lower and upper value for each breakpoint (there are
  // numberOfSegments+1).
  for (auto segIdx = 0; segIdx <= numberOfSegments; ++segIdx) {
    const auto tValue = static_cast<double>(segIdx) / numberOfSegments;

    // Compute the linear contribution to the component values of the slefe.
    lowerValues[segIdx] = aerp(tValue, lCoeff, rCoeff);
    upperValues[segIdx] = aerp(tValue, lCoeff, rCoeff);

    // Add contribution from every coefficient of the basis functions.
    for (auto bsfIdx = 0; bsfIdx < numberOfBasisFunctions; ++bsfIdx) {
      // Computes the index of the first coefficient of the current basis
      // function.
      const auto offset = bsfIdx * numberOfCoefficients;

      if (secondDiffs[bsfIdx] > 0) {
        lowerValues[segIdx] +=
            lowerBounds[offset + segIdx] * secondDiffs[bsfIdx];
        upperValues[segIdx] +=
            upperBounds[offset + segIdx] * secondDiffs[bsfIdx];
      } else {
        lowerValues[segIdx] +=
            upperBounds[offset + segIdx] * secondDiffs[bsfIdx];
        upperValues[segIdx] +=
            lowerBounds[offset + segIdx] * secondDiffs[bsfIdx];
      }
    }
  }

  return UniSlefe(lowerValues, upperValues);
}

double UniSlefeBuilder::aerp(double t, double a, double b) const {
  if (t < 0.0 || t > 1.0) {
    throw std::invalid_argument(
        "The weight must be a number in the real line interval [0,1]");
  }

  return std::clamp((1.0 - t) * a + t * b, std::min(a, b), std::max(a, b));
}
} // namespace slefe
