#include <gtest/gtest.h>
#include <stdexcept>

#include "../Matrix/Matrix.hpp"
#include "GramSchmidt.hpp"

TEST(QRGramSchmidt, ProjAU)
{
  std::vector<double> v1({3, 4});
  std::vector<double> v2({1, 0});

  std::vector<double> expectedV({3, 0});

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