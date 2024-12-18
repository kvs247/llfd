#include <stdlib.h>
#include <initializer_list>
#include <vector>
#include <iostream>
#include <stdexcept>

class Matrix
{
public:
  Matrix() = delete;
  Matrix(const std::vector<std::vector<double>>);

  void print(std::ostream &os) const
  {
    for (size_t i = 0; i < data.size(); ++i)
    {
      if (i % nCol == 0)
      {
        os << "|";
      }

      os << " " << data[i];

      if ((i + 1) % nCol == 0)
      {
        os << " |\n";
      }
    }
  }

private:
  const size_t nRow = 0;
  const size_t nCol = 0;
  std::vector<double> data;
};