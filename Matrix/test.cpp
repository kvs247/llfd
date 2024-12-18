#include <gtest/gtest.h>
#include <stdexcept>

#include "Matrix.hpp"

TEST(Matrix, CanCreateValidMatrix)
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

TEST(Matrix, ThrowsOnCreateInvalidMatrix)
{
  EXPECT_THROW(Matrix m({{1, 2}, {3, 4, 5}}), std::invalid_argument);
}
