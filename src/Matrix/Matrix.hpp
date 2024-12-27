#pragma once

#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <vector>

using Vector2D = std::vector<std::vector<double>>;

class Matrix
{
public:
  Matrix() = delete;
  Matrix(const Matrix &) = default;
  Matrix(const Vector2D &);
  Matrix(const std::vector<double> &eles, const size_t rows, const size_t cols);

  size_t getNRows() const;
  size_t getNCols() const;
  Vector2D getRows() const;
  Vector2D getCols() const;

  static bool isSameDimension(const Matrix &m1, const Matrix &m2);
  static Matrix makeIdentityMatrix(const size_t n);

  void print(std::ostream &os) const;
  double at(size_t i, size_t j) const;
  Matrix &transpose();
  Matrix transpose() const;

  Matrix &operator=(const Matrix &);
  bool operator==(const Matrix &) const;
  Matrix &operator+=(const Matrix &);
  Matrix operator+(const Matrix &) const;
  Matrix &operator-=(const Matrix &);
  Matrix operator-(const Matrix &) const;
  Matrix &operator*=(const Matrix &);
  Matrix operator*(const Matrix &) const;

private:
  size_t nRows = 0;
  size_t nCols = 0;
  std::vector<double> data;
};
