#include <gtest/gtest.h>
#include <stdexcept>

#include "Matrix.hpp"

// constructors
TEST(Matrix, CanCreateValidMatrix2D)
{
  Matrix m({{1, 2}, {3, 4}, {5, 6}});

  size_t expectedNRows = 3;
  size_t expectedNCols = 2;
  Vector2D expectedRows = {
      {1, 2},
      {3, 4},
      {5, 6},
  };
  Vector2D expectedCols = {
      {1, 3, 5},
      {2, 4, 6},
  };

  EXPECT_EQ(m.getNRows(), expectedNRows);
  EXPECT_EQ(m.getNCols(), expectedNCols);

  EXPECT_EQ(m.getRows(), expectedRows);
  EXPECT_EQ(m.getCols(), expectedCols);
}

TEST(Matrix, ThrowsOnCreateInvalidMatrix2D) { EXPECT_THROW(Matrix m({{1, 2}, {3, 4, 5}}), std::invalid_argument); }

TEST(Matrix, CanCreateValidMatrix1D)
{
  Matrix m({1, 2, 3, 4, 5, 6}, 3, 2);

  size_t expectedNRows = 3;
  size_t expectedNCols = 2;
  Vector2D expectedRows = {
      {1, 2},
      {3, 4},
      {5, 6},
  };
  Vector2D expectedCols = {
      {1, 3, 5},
      {2, 4, 6},
  };

  EXPECT_EQ(m.getNRows(), expectedNRows);
  EXPECT_EQ(m.getNCols(), expectedNCols);

  EXPECT_EQ(m.getRows(), expectedRows);
  EXPECT_EQ(m.getCols(), expectedCols);
}

TEST(Matrix, ThrowsOnCreateInvalidMatrix1D) { EXPECT_THROW(Matrix m({1, 2, 3, 4, 5}, 3, 2), std::invalid_argument); }

// getters
TEST(Matrix, GetDiagonal)
{
  Matrix m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  const std::vector<double> expected{1, 5, 9};

  EXPECT_EQ(m.getDiagonal(), expected);
}

TEST(Matrix, GetDiagonalNonSquareMatrix)
{
  Matrix m({{1, 2, 3}, {4, 5, 6}});

  EXPECT_THROW(m.getDiagonal(), std::invalid_argument);
}

// public methods
TEST(Matrix, IsSquare)
{
  Matrix m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix m2({{1, 2, 3}, {4, 5, 6}});

  EXPECT_TRUE(Matrix::isSquare(m1));
  EXPECT_TRUE(m1.isSquare());

  EXPECT_FALSE(Matrix::isSquare(m2));
  EXPECT_FALSE(m2.isSquare());
}

TEST(Matrix, IsSameDimension)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{0, 1}, {1, 0}, {0, 1}});
  Matrix m3({{1, 0}, {0, 1}});

  EXPECT_TRUE(Matrix::isSameDimension(m1, m2));
  EXPECT_FALSE(Matrix::isSameDimension(m1, m3));
  EXPECT_FALSE(Matrix::isSameDimension(m2, m3));
}

TEST(Matrix, MakeIdentityMatrix)
{
  size_t dim = 4;

  Matrix expected({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});

  EXPECT_EQ(Matrix::makeIdentityMatrix(dim), expected);
}

TEST(Matrix, AtWithValidInput)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});

  EXPECT_EQ(m1.at(0, 0), 1);
  EXPECT_EQ(m1.at(1, 0), 3);
  EXPECT_EQ(m1.at(2, 0), 5);
  EXPECT_EQ(m1.at(0, 1), 2);
  EXPECT_EQ(m1.at(1, 1), 4);
  EXPECT_EQ(m1.at(2, 1), 6);
}

TEST(Matrix, AtWithInvalidInput)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});

  EXPECT_THROW(m1.at(0, 2), std::out_of_range);
  EXPECT_THROW(m1.at(3, 0), std::out_of_range);
}

TEST(Matrix, InPlaceTranspose)
{
  Matrix m({{1, 2, 3}, {4, 5, 6}});
  Matrix mt({{1, 4}, {2, 5}, {3, 6}});

  m.transpose();

  EXPECT_EQ(m, mt);
}

TEST(Matrix, ConstTranspose)
{
  Matrix m({{1, 2, 3}, {4, 5, 6}});
  Matrix mt({{1, 4}, {2, 5}, {3, 6}});

  EXPECT_EQ(m.transpose(), mt);
}

// operators
TEST(Matrix, Assignment)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 2, 3}, {4, 5, 6}});

  m1 = m2;

  EXPECT_TRUE(m1 == m2);
}

TEST(Matrix, MatrixEquality)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 2}, {3, 4}, {5, 6}});
  Matrix m3({{1, 0}, {0, 1}});
  Matrix m4({{1, 2, 3}, {4, 5, 6}});

  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
  EXPECT_FALSE(m1 == m4);
}

TEST(Matrix, CanPlusEqualTwoMatrices)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 0}, {-2, 3}, {0, -9}});

  Matrix expectedMatrix({{2, 2}, {1, 7}, {5, -3}});

  m1 += m2;
  EXPECT_EQ(m1, expectedMatrix);
}

TEST(Matrix, CannotPlusEqualUnequalDimensionMatrices)
{
  Matrix m1({{0, 1}, {1, 0}, {0, 1}});
  Matrix m2({{1, 0}, {0, 1}});

  EXPECT_THROW(m1 += m2, std::invalid_argument);
}

TEST(Matrix, CanAddTwoMatrices)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 0}, {-2, 3}, {0, -9}});

  Matrix expectedMatrix({{2, 2}, {1, 7}, {5, -3}});

  EXPECT_EQ(m1 + m2, expectedMatrix);
}

TEST(Matrix, CannotAddUnequalDimensionMatrices)
{
  Matrix m1({{0, 1}, {1, 0}, {0, 1}});
  Matrix m2({{1, 0}, {0, 1}});

  EXPECT_THROW(m1 + m2, std::invalid_argument);
}

TEST(Matrix, CanMinusEqualTwoMatrices)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 0}, {-2, 3}, {0, -9}});

  Matrix expectedMatrix({{0, 2}, {5, 1}, {5, 15}});

  m1 -= m2;
  EXPECT_EQ(m1, expectedMatrix);
}

TEST(Matrix, CannotMinusEqualUnequalDimensionMatrices)
{
  Matrix m1({{0, 1}, {1, 0}, {0, 1}});
  Matrix m2({{1, 0}, {0, 1}});

  EXPECT_THROW(m1 -= m2, std::invalid_argument);
}

TEST(Matrix, CanSubtractTwoMatrices)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 0}, {-2, 3}, {0, -9}});

  Matrix expectedMatrix({{0, 2}, {5, 1}, {5, 15}});

  EXPECT_EQ(m1 - m2, expectedMatrix);
}

TEST(Matrix, CannotSubtractUnequalDimensionMatrices)
{
  Matrix m1({{0, 1}, {1, 0}, {0, 1}});
  Matrix m2({{1, 0}, {0, 1}});

  EXPECT_THROW(m1 - m2, std::invalid_argument);
}

TEST(Matrix, CanStarEqualTwoMatrices)
{
  Matrix m1({{1, 2, 3}, {4, 5, 6}});
  Matrix m2({{0, 1, 1}, {2, 3, 5}, {8, 13, 21}});

  Matrix expectedMatrix({{28, 46, 74}, {58, 97, 155}});

  m1 *= m2;
  EXPECT_EQ(m1, expectedMatrix);
}

TEST(Matrix, CannotStarEqualInvalidMatrixDimensions)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{0, 1, 1}, {2, 3, 5}, {8, 13, 21}});

  EXPECT_THROW(m1 *= m2, std::invalid_argument);
}

TEST(Matrix, CanMultiplyTwoMatrices)
{
  Matrix m1({{1, 2, 3}, {4, 5, 6}});
  Matrix m2({{0, 1, 1}, {2, 3, 5}, {8, 13, 21}});

  Matrix expectedMatrix({{28, 46, 74}, {58, 97, 155}});

  EXPECT_EQ(m1 * m2, expectedMatrix);
}

TEST(Matrix, CannotMultiplyInvalidMatrixDimensions)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{0, 1, 1}, {2, 3, 5}, {8, 13, 21}});

  EXPECT_THROW(m1 * m2, std::invalid_argument);
}