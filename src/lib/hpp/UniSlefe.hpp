#pragma once

#include <vector>

namespace slefe {
class UniSlefe {
public:
  /**
   * \fn UniSlefe()
   * \brief Creates a slefe for a univariate function.
   * \param lower The values of the upper component of the slefe at the
   * breakpoints. \param upper The values of the lower component of the slefe at
   * the breakpoints.
   */
  UniSlefe(const std::vector<double> &lower, const std::vector<double> &upper);

  /**
   * \fn lowerValueAt()
   * \brief Computes the value of the lower component of the slefe at a given
   * parameter value. \param t A parameter value in the interval [0,1]. \return
   * The value of the lower component of the slefe at \c t.
   */
  double lowerValueAt(double t) const;

  /**
   * \fn upperValueAt()
   * \brief Computes the value of the upper component of the slefe at a given
   * parameter value. \param t A parameter value in the interval [0,1]. \return
   * The value of the upper component of the slefe at \c t.
   */
  double upperValueAt(double t) const;

  /**
   * \fn lowerValues()
   * \brief Returns the values of the lower component of the slefe at the
   * breakpoints. \return The values of the lower component of the slefe at the
   * breakpoints.
   */
  const std::vector<double> &lowerValues() const;

  /**
   * \fn lowerValues()
   * \brief Returns the values of the upper component of the slefe at the
   * breakpoints. \return The values of the upper component of the slefe at the
   * breakpoints.
   */
  const std::vector<double> &upperValues() const;

private:
  /** The number of segments of the slefe. */
  int _numberOfSegments;

  /** The values of the lower component of the slefe. */
  std::vector<double> _lower;

  /** The values of the upper component of the slefe. */
  std::vector<double> _upper;
};

} // namespace slefe
