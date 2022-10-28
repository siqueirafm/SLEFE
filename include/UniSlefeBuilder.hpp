#pragma once

#include "UniSlefe.hpp"

#include <vector>

namespace slefe {
class UniSlefeBuilder {
public:
  /** Default constructor. */
  UniSlefeBuilder() = default;

  /**
   * \fn build()
   * \brief Builds a slefe for a univariate Bézier function of a given degree.
   * \param degree Degree of the Bézier function.
   * \param numberOfSegments Number of linear pieces in the slefe.
   * \param coeffs Array with the Bézier coefficients of the function.
   * \return A slefe for the given univariate function.
   */
  UniSlefe build(int degree, int numberOfSegments,
                 const std::vector<double> &coeffs) const;

private:
  /** Computes the affine combination of two values. */
  double aerp(double t, double a, double b) const;

public:
  /** Maximum degree of a polynomial basis function. */
  constexpr static int MaximumDegree = 9;

  /** Maximum number of linear segments of a slefe. */
  constexpr static int MaximumNumberOfSegments = 9;

  /** Data type for the pre-tabulated upper and lower bounds. */
  using UniSlefeTableType = std::vector<std::vector<std::vector<double>>>;

  /** Table of upper bounds of slefes for univariate functions. */
  static const UniSlefeTableType UpperBounds;

  /** Table of lower bounds of slefes for univariate functions. */
  static const UniSlefeTableType LowerBounds;
};

} // namespace slefe
