#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "../Matrix/Matrix.hpp"
#include "GramSchmidt.hpp"

// std::pair<Matrix, Matrix> getQRDecomp(const Matrix &m)
// {
//   // return {{{}}, {{}}};
// }

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