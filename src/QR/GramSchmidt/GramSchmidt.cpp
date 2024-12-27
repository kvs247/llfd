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

  std::vector<std::vector<double>> uVecs;
  std::vector<std::vector<double>> newBasis;

  for (size_t i = 0; i < cols.size(); ++i)
  {
    auto newU = cols[i];
    auto c = cols[i];

    for (size_t j = 0; j < i; ++j)
    {
      auto proj = projAOntoU(c, uVecs[j]);
      for (size_t k = 0; k < newU.size(); ++k)
      {
        newU[k] -= proj[k];
      }
    }
    uVecs.push_back(newU);
    newBasis.push_back(QR_GS::normalize(newU));
  }

  const auto q = Matrix(newBasis).transpose();
  const auto r = computeR(newBasis, cols);

  return {q, r};
}

std::vector<double> QR_GS::projAOntoU(std::vector<double> &a, std::vector<double> &u)
{
  const auto ua = innerProduct(u, a);
  const auto uu = innerProduct(u, u);

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