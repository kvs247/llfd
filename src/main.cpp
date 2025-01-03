#include <iostream>
#include <kmath/Matrix/Eigen.hpp>
#include <kmath/Matrix/Matrix.hpp>

#include "QRAlgo/QRAlgo.hpp"
#include "QRDecomp/GramSchmidt/GramSchmidt.hpp"

int main()
{
  // Matrix m({{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}});
  // Matrix m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  // Matrix m({{2, -2, 18}, {2, 1, 0}, {1, 2, 0}});
  // Matrix m({
  //     {2, 0, -1, -1, 0},
  //     {0, 0, 0, 0, 0},
  //     {-1, 0, 1, 0, 0},
  //     {-1, 0, 0, 1, 0},
  //     {0, 0, 0, 0, 0},
  // });

  Matrix m({
      {1, -1, 0},
      {-1, 2, -1},
      {0, -1, 1},
  });

  const auto res = Eigen::compute(m);

  for (const auto &x : res)
  {
    std::cout << "λ = " << x.first << "\n";
    for (auto &v : x.second)
    {
      std::cout << "\t[ ";
      for (size_t i = 0; i < v.size(); ++i)
      {
        std::cout << v.at(i) << " ";
      }
      std::cout << "]\n";
    }
    std::cout << "\n";
  }
}