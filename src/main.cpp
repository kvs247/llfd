#include <bitset>
#include <iostream>
#include <kmath/Matrix/Eigen.hpp>
#include <kmath/Matrix/Matrix.hpp>
#include <vector>

#include <cmath>

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

  // Matrix m({{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}});
  // Matrix m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  // Matrix m({{2, -2, 18}, {2, 1, 0}, {1, 2, 0}});
  // Matrix m({
  //     {2, 0, -1, -1, 0},
  //     {0, 0, 0, 0, 0},
  //     {-1, 0, 1, 0, 0},
  //     {-1, 0, 0, 1, 0},
  //     {0, 0, 0, 0, 0},
  // });

  // Matrix m({
  //     {1, -1, 0},
  //     {-1, 2, -1},
  //     {0, -1, 1},
  // });

  for (const auto &m : f())
  {
    m.print();
    const auto res = Eigen::compute(m);

    for (const auto &x : res)
    {
      std::cout << "λ = " << x.first << "\n";
      for (auto &v : x.second)
      {
        std::cout << "\t[ ";
        for (size_t i = 0; i < v.size(); ++i)
        {
          std::cout << v.at(i) << " ";
        }
        std::cout << "]\n";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }
}