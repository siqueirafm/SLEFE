#include "UniSlefe.hpp"

#include <stdexcept>

namespace slefe {
namespace {
/**
 * Returns the value of the piecewise-affine hat function at a given parameter
 * value.
 */
double hatFunction(double t, int numberOfSegments) {
  const auto breakpoint = 1.0 / numberOfSegments;

  if (t <= -breakpoint) {
    return 0.0;
  }

  if (t <= 0.0) {
    return numberOfSegments * t + 1.0;
  }

  if (t <= breakpoint) {
    return 1.0 - numberOfSegments * t;
  }

  return 0.0;
}

/**
 * Returns the result of the piecewise affine interpolation a set of values. The
 * coefficients associated with the values are given by a hat-function evaluated
 * at a given parameter value.
 */
double interpolate(const std::vector<double> &values, int numberOfSegments,
                   double t) {
  auto result = 0.0;

  for (auto idx = 0; idx <= numberOfSegments; ++idx) {
    const auto u = t - static_cast<double>(idx) / numberOfSegments;
    result += values[idx] * hatFunction(u, numberOfSegments);
  }

  return result;
}
} // namespace

UniSlefe::UniSlefe(const std::vector<double> &lower,
                   const std::vector<double> &upper)
    : _lower(lower), _upper(upper) {
  const auto numberOfValues = _lower.size();

  if (numberOfValues != _upper.size()) {
    throw std::invalid_argument("The number of values of the lower and upper "
                                "envelopes must be the same");
  }

  if (numberOfValues < 2) {
    throw std::invalid_argument("The number of values of the lower and upper "
                                "envelopes must be greater than 1");
  }

  _numberOfSegments = static_cast<int>(numberOfValues) - 1;
}

double UniSlefe::lowerValueAt(double t) const {
  if (t < 0.0 || t > 1.0) {
    throw std::invalid_argument(
        "The parameter value must be a number in the real line interval [0,1]");
  }

  return interpolate(_lower, _numberOfSegments, t);
}

double UniSlefe::upperValueAt(double t) const {
  if (t < 0.0 || t > 1.0) {
    throw std::invalid_argument(
        "The parameter value must be a number in the real line interval [0,1]");
  }

  return interpolate(_upper, _numberOfSegments, t);
}

const std::vector<double> &UniSlefe::lowerValues() const { return _lower; }

const std::vector<double> &UniSlefe::upperValues() const { return _upper; }

} // namespace slefe
