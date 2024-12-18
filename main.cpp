#include <iostream>

#include "Matrix/Matrix.hpp"

int main()
{
  const std::vector<std::vector<double>> eles{{{1,2,3},{4,5,6},{7,8,9}}};
  Matrix m(eles);

  m.print(std::cout);
}