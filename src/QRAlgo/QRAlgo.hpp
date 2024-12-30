#pragma once

#include <kmath/Matrix/Matrix.hpp>
#include <map>
#include <vector>

class QR_Algo
{
public:
  static std::map<double, std::vector<std::vector<double>>> qrAlgo(Matrix &);
};