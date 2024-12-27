#pragma once

#include <utility>
#include <vector>

#include "../../Matrix/Matrix.hpp"

class QR_GS
{
public:
  static std::pair<Matrix, Matrix> GramSchmidtDecompositon(const Matrix &);
  static std::vector<double> projAOntoU(std::vector<double> &a, std::vector<double> &u);
  static double innerProduct(const std::vector<double> &v, const std::vector<double> &w);
  static std::vector<double> normalize(std::vector<double> &v);
};