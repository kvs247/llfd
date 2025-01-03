#pragma once

#include <kmath/Matrix/Matrix.hpp>
#include <memory>
#include <utility>
#include <vector>

class QR_GS
{
public:
  static std::pair<Matrix, Matrix> qrDecomp(const Matrix &);
  static Matrix computeR(const std::vector<Vector> &basis, const std::vector<std::shared_ptr<Vector>> &colPtrs);
};