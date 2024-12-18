#include <initializer_list>
#include <iostream>
#include <span>
#include <stdexcept>
#include <vector>

#include "Matrix.hpp"

// constructors
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

Matrix::Matrix(const std::vector<double> &eles, const size_t rows, const size_t cols)
    : nRows(rows), nCols(cols), data(eles)
{
  if (data.size() != rows * cols)
  {
    throw std::invalid_argument("Matrix of dimension n x m must have (n*m) elements");
  }
}

// getters
size_t Matrix::getNRows() const { return nRows; }
size_t Matrix::getNCols() const { return nCols; }

Vector2D Matrix::getRows() const
{
  Vector2D rows(nRows, std::vector<double>(nCols));

  for (size_t i = 0; i < nRows; ++i)
  {
    for (size_t j = 0; j < nCols; ++j)
    {
      rows[i][j] = data[j + nCols * i];
    }
  }

  return rows;
}

Vector2D Matrix::getCols() const
{
  Vector2D cols(nCols, std::vector<double>(nRows));

  for (size_t i = 0; i < nCols; ++i)
  {
    for (size_t j = 0; j < nRows; ++j)
    {
      cols[i][j] = data[i + j * nCols];
    }
  }

  return cols;
}

// static methods
bool Matrix::isSameDimension(const Matrix &m1, const Matrix &m2)
{
  return m1.nRows == m2.nRows && m1.nCols == m2.nCols;
}

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

double Matrix::at(size_t i, size_t j) const
{
  if (i >= this->nRows || j >= this->nCols)
  {
    throw std::out_of_range("Matrix index is outside of valid range");
  }

  return data[j + i * nCols];
}

// operators
Matrix &Matrix::operator=(const Matrix &other)
{
  this->data = other.data;
  this->nRows = other.nRows;
  this->nCols = other.nCols;

  return *this;
}

bool Matrix::operator==(const Matrix &other) const
{
  if (!isSameDimension(*this, other))
  {
    return false;
  }

  return this->data == other.data;
};

Matrix &Matrix::operator+=(const Matrix &other)
{
  if (!Matrix::isSameDimension(*this, other))
  {
    throw std::invalid_argument("Matrices must be equal dimension for addition");
  };

  std::vector<double> sumData(this->data.size());
  for (size_t i = 0; i < this->data.size(); ++i)
  {
    this->data[i] = this->data[i] + other.data[i];
  }

  return *this;
};

Matrix Matrix::operator+(const Matrix &other) const { return Matrix(*this) += other; }

Matrix &Matrix::operator-=(const Matrix &other)
{
  if (!Matrix::isSameDimension(*this, other))
  {
    throw std::invalid_argument("Matrices must be equal dimension for subtraction");
  };

  std::vector<double> differenceData(this->data.size());
  for (size_t i = 0; i < this->data.size(); ++i)
  {
    this->data[i] = this->data[i] - other.data[i];
  }

  return *this;
}

Matrix Matrix::operator-(const Matrix &other) const { return Matrix(*this) -= other; }

Matrix &Matrix::operator*=(const Matrix &other)
{
  if (this->nCols != other.nRows)
  {
    throw std::invalid_argument("Invalid shapes for matrix multiplication");
  }

  const auto newNRows = this->nRows;
  const auto newNCols = other.nCols;
  auto newData = std::vector<double>(newNRows * newNCols, 0.0);

  for (size_t row = 0; row < newNRows; ++row)
  {
    for (size_t k = 0; k < this->nCols; ++k)
    {
      const auto thisMatrixValue = this->at(row, k);
      for (size_t col = 0; col < newNCols; ++col)
      {
        newData[col + newNCols * row] += thisMatrixValue * other.at(k, col);
      }
    }
  }

  this->nRows = newNRows;
  this->nCols = newNCols;
  this->data = std::move(newData);

  return *this;
}

Matrix Matrix::operator*(const Matrix &other) const { return Matrix(*this) *= other; }
