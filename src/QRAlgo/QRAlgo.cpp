#include <iostream>
#include <kmath/Matrix/Matrix.hpp>
#include <kmath/Matrix/Vector.hpp>
#include <map>
#include <vector>

#include "../QRDecomp/GramSchmidt/GramSchmidt.hpp"
#include "QRAlgo.hpp"

std::map<double, std::vector<Vector>> QR_Algo::qrAlgo(Matrix &m)
{
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
  const Matrix lastTwoRatio(newData, m.getNRows(), m.getNCols());

  const auto orderedEigenVals = lastTwoRatio.getDiagonal();
  const auto orderedEigenVectors = u.getCols();

  if (orderedEigenVals.size() != orderedEigenVectors.size())
  {
    throw std::runtime_error("orderedEigenVals and orderedEigenVectos have unequal size");
  }

  std::map<double, std::vector<Vector>> res;
  for (size_t i = 0; i < orderedEigenVals.size(); ++i)
  {
    auto &entry = res[orderedEigenVals[i]];
    entry.push_back(*orderedEigenVectors[i]);
  }
  return res;
}