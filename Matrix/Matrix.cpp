#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <span>

#include "Matrix.hpp"

Matrix::Matrix(const std::vector<std::vector<double>> rows) : nRow(rows.size()), nCol(rows.begin()->size())
{
  if (!rows.size())
  {
    throw std::invalid_argument("Matrix cannot be empty");
  }

  data.reserve(nRow * nCol);
  auto dataIt = data.begin();

  for (auto it = rows.begin(); it != rows.end(); ++it)
  {
    const auto row = *it;
    if (row.size() != nCol)
    {
      throw std::invalid_argument("Matrix rows must have the same length");
    }

    data.insert(dataIt, row.cbegin(), row.cend());
    dataIt += nCol;
  }
}
