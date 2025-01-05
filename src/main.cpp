#include <bitset>
#include <iomanip>
#include <iostream>
#include <kmath/Matrix/Eigen.hpp>
#include <kmath/Matrix/Matrix.hpp>
#include <vector>

#include <cmath>

void printMatrixEigenstate(const Matrix &m, const std::map<double, std::vector<Vector>> &eState)
{
  m.print();

  const auto origFlags = std::cout.flags();
  const auto origPrecision = std::cout.precision();
  std::cout << std::fixed << std::setprecision(2);

  std::vector<std::string> lines;
  for (const auto &[eVal, eVecs] : eState)
  {
    for (size_t i = 0; i < eVecs[0].size(); ++i)
    {
      std::cout << "\t";
      if (i == eVecs[0].size() / 2)
      {
        std::cout << "λ: " << eVal << " ";
      }
      else
      {
        std::cout << std::string(8, ' ');
      }
      std::cout << "|";
      for (size_t j = 0; j < eVecs.size(); ++j)
      {
        std::cout << std::setw(5) << eVecs[j].at(i) << "|";
        if (j < eVecs.size() - 1)
        {
          std::cout << "  |";
        }
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }
}

std::vector<Matrix> f()
{
  // get int values
  constexpr size_t n = 3;
  constexpr size_t numEdges = n * (n - 1) / 2;
  size_t numMats = std::pow(2, numEdges);

  // generate matrices
  std::vector<Matrix> res;
  for (size_t i = 0; i < numMats; ++i)
  {
    // get bitstring representing upper triangle
    std::vector<double> data(n * n);
    const auto s = std::bitset<numEdges>(i).to_string();

    // fill upper triangle
    size_t sIdx = 0;
    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = 0; j < n; ++j)
      {

        if (j > i)
        {
          const int val = s[sIdx++] - '0';
          data[i * n + j] = -val;
        }
      }
    }

    // symmetrize
    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = 0; j < n; ++j)
      {
        if (i > j)
        {
          data[i * n + j] = data[j * n + i];
        }
      }
    }

    // diagonal values
    for (size_t i = 0; i < n; ++i)
    {
      size_t count = 0;
      for (size_t j = 0; j < n; ++j)
      {
        count -= data[i * n + j];
      }
      data[i * n + i] = count;
    }

    res.push_back(Matrix(data, n, n));
  }

  return res;
}

int main()
{
  f();

  for (const auto &m : f())
  {
    const auto res = Eigen::compute(m);

    printMatrixEigenstate(m, res);
    std::cout << "\n";
  }
}