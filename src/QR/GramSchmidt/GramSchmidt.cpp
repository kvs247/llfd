#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "../../Matrix/Matrix.hpp"
#include "GramSchmidt.hpp"

std::pair<Matrix, Matrix> QR_GS::qrDecomp(const Matrix &m)
{
  const auto cols = m.getCols();
  auto firstCol = cols.front();

  std::vector<std::vector<double>> uVecs({firstCol});
  std::vector<std::vector<double>> newBasis({normalize(firstCol)});

  for (size_t i = 1; i < cols.size(); ++i)
  {
    auto col = cols[i];
    const auto firstThisUVec = subtractVectors(col, projAOntoU(col, uVecs.front()));
    std::vector<std::vector<double>> thisUVecs({firstThisUVec});

    for (size_t k = 1; k < i; ++k)
    {
      const auto newThisUVec = subtractVectors(thisUVecs.back(), projAOntoU(thisUVecs.back(), uVecs[k]));
      thisUVecs.push_back(newThisUVec);
    }

    uVecs.push_back(thisUVecs.back());
    newBasis.push_back(QR_GS::normalize(thisUVecs.back()));
  }

  const auto q = Matrix(newBasis).transpose();
  const auto r = computeR(newBasis, cols);

  return {q, r};
}

std::vector<double> QR_GS::projAOntoU(std::vector<double> &a, std::vector<double> &u)
{
  const auto ua = innerProduct(u, a);
  const auto uu = innerProduct(u, u);

  if (uu == 0)
  {
    return std::vector(u.size(), 0.0);
  }

  auto res = u;
  std::transform(res.cbegin(), res.cend(), res.begin(), [&](double x) { return ua / uu * x; });

  return res;
}

double QR_GS::innerProduct(const std::vector<double> &v, const std::vector<double> &w)
{
  if (v.size() != w.size())
  {
    throw std::invalid_argument("Input vectors to inner product must have equal dimension");
  }

  double res = 0;
  for (size_t i = 0; i < v.size(); ++i)
  {
    res += v[i] * w[i];
  }
  return res;
}

std::vector<double> QR_GS::normalize(std::vector<double> &v)
{
  double norm = 0;
  for (auto &x : v)
  {
    norm += x * x;
  }
  norm = std::sqrt(norm);

  if (norm == 0)
  {
    return v;
  }

  for (auto &x : v)
  {
    x /= norm;
  }

  return v;
}

Matrix QR_GS::computeR(const std::vector<std::vector<double>> &basis, const std::vector<std::vector<double>> &cols)
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

      auto val = innerProduct(basis[i], cols[j]);
      if (std::abs(val) < 1e-10)
      {
        val = 0;
      }
      rData[i * n + j] = val;
    }
  }
  return Matrix(rData, n, n);
}

std::vector<double> QR_GS::subtractVectors(const std::vector<double> &v1, const std::vector<double> &v2)
{
  if (v1.size() != v2.size())
  {
    throw std::invalid_argument("Vectors must be equal length for subtraction");
  }

  const size_t n = v1.size();
  std::vector<double> res(n);
  for (size_t i = 0; i < n; ++i)
  {
    res[i] = v1[i] - v2[i];
  }
  return res;
}