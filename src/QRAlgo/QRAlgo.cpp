#include <iostream>

#include "QRAlgo.hpp"
#include "../QRDecomp/GramSchmidt/GramSchmidt.hpp"

void QR_Algo::qrAlgo(Matrix &m) {
  const int ITERATIONS = 20;

  Matrix u = Matrix::makeIdentityMatrix(m.getNCols());
  Matrix lastM = m;

  for (size_t k = 0; k < ITERATIONS; ++k)
  {
    const auto qrDecomp = QR_GS::qrDecomp(m);
    const auto q = qrDecomp.first;
    const auto r = qrDecomp.second;

    lastM = m;
    m = r * q;

    u *= q;

    std::cout << k << ":\n";
    m.print(std::cout);
  }

  auto newData = m.getData();
  auto lastMData = lastM.getData();
  for (size_t i = 0; i < newData.size(); ++i)
  {
    if (lastMData[i] == 0)
    {
      continue;
    }
    newData[i] /= lastMData[i];
  }
  std::cout << "ratio:\n";
  Matrix(newData, m.getNRows(), m.getNCols()).print(std::cout);

  std::cout << "U:\n";
  u.print();
}