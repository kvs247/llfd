#include <stdlib.h>
#include <initializer_list>
#include <vector>
#include <iostream>
#include <stdexcept>

using Vector2D = std::vector<std::vector<double>>;

class Matrix
{
public:
  Matrix() = delete;
  Matrix(const Vector2D&);

  size_t getNRows() const;
  size_t getNCols() const;
  Vector2D getRows() const;
  Vector2D getCols() const;

  void print(std::ostream &os) const;

private:
  const size_t nRows = 0;
  const size_t nCols = 0;
  std::vector<double> data;
};
