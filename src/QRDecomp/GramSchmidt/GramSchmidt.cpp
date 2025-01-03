#include <algorithm>
#include <cmath>
#include <iostream>
#include <kmath/Matrix/Matrix.hpp>
#include <kmath/Matrix/Vector.hpp>
#include <stdexcept>
#include <utility>

#include "GramSchmidt.hpp"

std::pair<Matrix, Matrix> QR_GS::qrDecomp(const Matrix &m)
{
  const auto colPtrs = m.getCols();
  auto firstCol = *colPtrs.front();
  std::vector<Vector> uVecs({firstCol});
  std::vector<Vector> newBasis({firstCol.normalize()});

  for (size_t i = 1; i < colPtrs.size(); ++i)
  {
    auto col = *colPtrs[i];
    const auto firstThisUVec = col - Vector(col).proj(uVecs.front());
    std::vector<Vector> thisUVecs({firstThisUVec});

    for (size_t k = 1; k < i; ++k)
    {
      const auto newThisUVec = thisUVecs.back() - Vector(thisUVecs.back()).proj(uVecs[k]);
      thisUVecs.push_back(newThisUVec);
    }

    uVecs.push_back(thisUVecs.back());
    newBasis.push_back(thisUVecs.back().normalize());
  }

  const auto q = Matrix(newBasis);
  const auto r = computeR(newBasis, colPtrs);

  return {q, r};
}

Matrix QR_GS::computeR(const std::vector<Vector> &basis, const std::vector<std::shared_ptr<Vector>> &colPtrs)
{
  const auto n = basis.size();
  std::vector<double> rData(n * n);
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      if (j > i)
      {
        rData[i * n + j] = 0;
      }

      auto val = basis[i].innerProduct(*colPtrs[j]);
      if (std::abs(val) < 1e-10)
      {
        val = 0;
      }
      rData[i * n + j] = val;
    }
  }
  return Matrix(rData, n, n);
}