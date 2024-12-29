#pragma once

#include <map>
#include <vector>

#include "../Matrix/Matrix.hpp"

class QR_Algo
{
public:
  static std::map<double, std::vector<std::vector<double>>> qrAlgo(Matrix &);
};