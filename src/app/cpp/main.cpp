#include <UniSlefeBuilder.hpp>

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace slefe;

void displaySlefeBreakpoints(int degree, const std::vector<double>& coeffs)
{
  UniSlefeBuilder builder;

  std::cout << std::fixed << std::setprecision(10);

  std::cout << std::endl;

  for (auto pieces = 1; pieces <= UniSlefeBuilder::MaximumNumberOfSegments; ++pieces)
  {
    std::cout << "Degree " << degree << ", " << pieces << " piece(s): " << std::endl;
    
    const auto slefe = builder.build(degree, pieces, coeffs);

    for (const auto& pt : slefe.upperValues())
    {
      std::cout << pt << "  ";
    }
    
    std::cout << std::endl;

    for (const auto& pt : slefe.lowerValues())
    {
      std::cout << pt << "  ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;
}

int main()
{
  std::vector<std::vector<double>> bezierCoeffs = {
    { 0.0, 1.0, 0.8 }, // degree 2
    { 0.0, 1.0, 0.8, -0.2 }, // degree 3
    { 0.0, 1.0, 0.8, -0.2, 2.5 }, // degree 4
    { 0.0, 1.0, 0.8, -0.2, 2.5, 3.5 }, // degree 5
    { 0.0, 1.0, 0.8, -0.2, 2.5, 3.5, 2.0 }, // degree 6
    { 0.0, 1.0, 0.8, -0.2, 2.5, 3.5, 2.0, 5.2 }, // degree 7
    { 0.0, 1.0, 0.8, -0.2, 2.5, 3.5, 2.0, 5.2, 4.0 }, // degree 8
    { 0.0, 1.0, 0.8, -0.2, 2.5, 3.5, 2.0, 5.2, 4.0, 0.5 } // degree 9
  };
  
  for (auto degree = 2; degree <= UniSlefeBuilder::MaximumDegree; ++degree)
  {
    displaySlefeBreakpoints(degree, bezierCoeffs[degree - 2]);    
  }

  return EXIT_SUCCESS;
}
