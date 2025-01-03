#pragma once

#include <kmath/Matrix/Matrix.hpp>
#include <kmath/Matrix/Vector.hpp>
#include <map>
#include <vector>

class QR_Algo
{
public:
  static std::map<double, std::vector<Vector>> qrAlgo(Matrix &);
};