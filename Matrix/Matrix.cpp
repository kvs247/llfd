#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <span>

#include "Matrix.hpp"

// constructors/destructors
Matrix::Matrix(const Vector2D &rows) : nRows(rows.size()), nCols(rows.begin()->size())
{
  if (!rows.size())
  {
    throw std::invalid_argument("Matrix cannot be empty");
  }

  data.reserve(nRows * nCols);
  auto dataIt = data.begin();

  for (auto it = rows.begin(); it != rows.end(); ++it)
  {
    const auto row = *it;
    if (row.size() != nCols)
    {
      throw std::invalid_argument("Matrix rows must have the same length");
    }

    data.insert(dataIt, row.cbegin(), row.cend());
    dataIt += nCols;
  }
}

// getters
size_t Matrix::getNRows() const { return nRows; }
size_t Matrix::getNCols() const { return nCols; }

Vector2D Matrix::getRows() const {
  Vector2D rows(nRows, std::vector<double>(nCols));

  for (size_t i = 0; i < nRows; ++i)
  {
    for (size_t j = 0; j < nCols; ++j)
    {
      rows[i][j] = data[j + nCols * i];    
    }
  }

  return rows;
};

Vector2D Matrix::getCols() const {
  Vector2D cols(nCols, std::vector<double>(nRows));

  for (size_t i = 0; i < nCols; ++i)
  {
    for (size_t j = 0; j < nRows; ++j)
    {
      cols[i][j] = data[i + j * nCols];
    }
  }

  return cols;
};

// public methods
void Matrix::print(std::ostream &os) const
{
  for (size_t i = 0; i < data.size(); ++i)
  {
    if (i % nCols == 0)
    {
      os << "|";
    }

    os << " " << data[i];

    if ((i + 1) % nCols == 0)
    {
      os << " |\n";
    }
  }
}
