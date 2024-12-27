#include <iostream>

#include "Matrix/Matrix.hpp"
#include "QR/GramSchmidt/GramSchmidt.hpp"

int main()
{
  // Matrix m({{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}});
  // Matrix m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  // Matrix m({{2, -2, 18}, {2, 1, 0}, {1, 2, 0}});
  Matrix m({
      {2, 0, -1, -1, 0},
      {0, 0, 0, 0, 0},
      {-1, 0, 1, 0, 0},
      {-1, 0, 0, 1, 0},
      {0, 0, 0, 0, 0},
  });

  const auto mQRDecomp = QR_GS::qrDecomp(m);
  const auto q = mQRDecomp.first;
  const auto r = mQRDecomp.second;
  const auto qr = q * r;

  std::cout << "main:\n";
  std::cout << "M:\n";
  m.print(std::cout);
  std::cout << "Q:\n";
  q.print(std::cout);
  std::cout << "R:\n";
  r.print(std::cout);
  std::cout << "Q * R:\n";
  qr.print(std::cout);
}