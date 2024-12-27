#include <gtest/gtest.h>
#include <stdexcept>

#include "../../Matrix/Matrix.hpp"
#include "GramSchmidt.hpp"

TEST(QRGramSchmidt, QRDecomposition)
{
  Matrix m({{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}});

  Matrix expectedQ({{6.0 / 7, -69.0 / 175, -58.0 / 175}, {3.0 / 7, 158.0 / 175, 6.0 / 175}, {-2.0 / 7, 6.0 / 35, -33.0 / 35}});
  Matrix expectedR({{14, 21, -14}, {0, 175, -70}, {0, 0, 35}});

  const auto res = QR_GS::qrDecomp(m);
  const auto q = res.first;
  const auto r = res.second;

  EXPECT_EQ(q, expectedQ);
  EXPECT_EQ(r, expectedR);
}

TEST(QRGramSchmidt, ProjAU)
{
  std::vector<double> v1({3, 4});
  std::vector<double> v2({1, 0});

  std::vector<double> expectedV({3, 0});

  EXPECT_EQ(QR_GS::projAOntoU(v1, v2), expectedV);
}

TEST(QRGramSchmidt, ProjAUWithUEqZero)
{
  std::vector<double> v1({3, 4});
  std::vector<double> v2({0, 0});

  std::vector<double> expectedV({0, 0});

  EXPECT_EQ(QR_GS::projAOntoU(v1, v2), expectedV);
}

TEST(QRGramSchmidt, InnerProduct)
{
  std::vector<double> v1({0.5, 1.2, -3.14});
  std::vector<double> v2({0, 0.8, 9.8});

  double expectedResult = -29.812;

  EXPECT_EQ(QR_GS::innerProduct(v1, v2), expectedResult);
}

TEST(QRGramSchmidt, InnerProductInvalidInput)
{
  std::vector<double> v1({1, 2, 3});
  std::vector<double> v2({1, 2, 5, 7});

  EXPECT_THROW(QR_GS::innerProduct(v1, v2), std::invalid_argument);
}

TEST(QRGramSchmidt, NormalizeVector)
{
  std::vector<double> v({3, 4, 12});
  std::vector<double> expectedV({3.0 / 13, 4.0 / 13, 12.0 / 13});

  EXPECT_EQ(QR_GS::normalize(v), expectedV);
}

TEST(QRGramSchmidt, NormalizeZeroVector)
{
  std::vector<double> v({0, 0, 0});

  EXPECT_EQ(QR_GS::normalize(v), v);
}

TEST(QRGramSchmidt, SubtractVector)
{
  std::vector<double> v1({1, 2, 3});
  std::vector<double> v2({0, -4, 1});

  std::vector<double> expected({1, 6, 2});

  EXPECT_EQ(QR_GS::subtractVectors(v1, v2), expected);
}

TEST(QRGramSchmidt, SubtractVectorsInvalidInput)
{
  std::vector<double> v1({1, 2, 3});
  std::vector<double> v2({0, -4});

  EXPECT_THROW(QR_GS::subtractVectors(v1, v2), std::invalid_argument);
}