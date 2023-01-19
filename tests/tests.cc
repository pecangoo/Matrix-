//#include <gtest/gtest.h>
#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(EqMatrix, Test_1) {
  S21Matrix a(3, 3), b(3, 3);
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  b.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  EXPECT_TRUE(a == b);
}

TEST(EqMatrix, Test_2) {
  S21Matrix a(3, 3), b(4, 3);
  EXPECT_FALSE(a == b);
}

TEST(EqMatrix, Test_3) {
  S21Matrix a(3, 3), b(3, 3);
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  b.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 1.);
  EXPECT_FALSE(a == b);
}

TEST(SumMatrix, Test_1) {
  S21Matrix a, c;
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  S21Matrix b(a);
  c.S21insertValues(9, 1. * 2, 2. * 2, 3. * 2, 4. * 2, 5. * 2, 6. * 2, 7. * 2,
                    8. * 2, 9. * 2);
  a = a + b;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(SumMatrix, Test_2) {
  S21Matrix a(1, 1), c(1, 1);
  a.S21insertValues(1, 1.);
  S21Matrix b(a);
  c.S21insertValues(1, 1. * 2);
  a += b;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(SumMatrix, Test_3) {
  S21Matrix a(3, 3), b(4, 3);
  EXPECT_ANY_THROW({ a.SumMatrix(b); });
}

TEST(SumMatrix, Test_4) {
  S21Matrix a(3, 3), b(3, 4);
  EXPECT_ANY_THROW({ a + b; });
}

TEST(SubMatrix, Test_1) {
  S21Matrix a, c;
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  S21Matrix b = a;
  c.S21insertValues(9, 0., 0., 0., 0., 0., 0., 0., 0., 0.);
  a -= b;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(SubMatrix, Test_2) {
  S21Matrix a(1, 1), c(1, 1);
  a.S21insertValues(1, 1.);
  S21Matrix b(a);
  c.S21insertValues(1, 0.);
  a = a - b;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(SubMatrix, Test_3) {
  S21Matrix a(3, 3), b(4, 3);
  EXPECT_ANY_THROW({ a - b; });
}

TEST(SubMatrix, Test_4) {
  S21Matrix a(3, 3), b(3, 4);
  EXPECT_ANY_THROW({ a.SubMatrix(b); });
}

TEST(MulNumber, Test_1) {
  S21Matrix a, c;
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  c.S21insertValues(9, 0., 0., 0., 0., 0., 0., 0., 0., 0.);
  a = a * 0.;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(MulNumber, Test_2) {
  S21Matrix a(2, 2), c(2, 2);
  a.S21insertValues(4, 1., 2., 3., 4.);
  c.S21insertValues(4, 1. * 2., 2. * 2., 3. * 2., 4. * 2.);
  a *= 2.;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(MulNumber, Test_3) {
  S21Matrix a(2, 2), c(2, 2);
  a.S21insertValues(4, 1., 2., 3., 4.);
  EXPECT_NO_THROW({ a * 1.5; });
}

TEST(MulNumber, Test_4) {
  S21Matrix a(2, 2), c(2, 2);
  a.S21insertValues(4, 1., 2., 3., 4.);
  EXPECT_NO_THROW({ 1.5 * a; });
}

TEST(MulMatrix, Test_1) {
  S21Matrix a(3, 2), b(2, 4), c(3, 4);
  a.S21insertValues(6, 1., 2., 3., 4., 5., 6.);
  b.S21insertValues(8, 1., 2., 3., 4., 5., 6., 7., 8.);
  c.S21insertValues(12, 11., 14., 17., 20., 23., 30., 37., 44., 35., 46., 57.,
                    68.);
  a *= b;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(MulMatrix, Test_2) {
  S21Matrix a(2, 2), b(2, 2), c(2, 2);
  a.S21insertValues(4, 1., 2., 3., 4.);
  b.S21insertValues(4, 5., 6., 7., 8.);
  c.S21insertValues(4, 19., 22., 43., 50.);
  a = a * b;
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(MulMatrix, Test_4) {
  S21Matrix a(3, 3), b(2, 2);
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  b.S21insertValues(4, 5., 6., 7., 8.);
  EXPECT_ANY_THROW(a.MulMatrix(b));
}

TEST(MulMatrix, Test_5) {
  S21Matrix a(3, 3), b(2, 2);
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  b.S21insertValues(4, 5., 6., 7., 8.);
  EXPECT_ANY_THROW(a *= b);
}

TEST(MulMatrix, Test_3) {
  S21Matrix a(3, 3), b(4, 3);
  EXPECT_ANY_THROW({ a *b; });
}

TEST(Transpose, Test_1) {
  S21Matrix a(3, 2), c(2, 3);
  a.S21insertValues(6, 1., 2., 3., 4., 5., 6.);
  c.S21insertValues(6, 1., 3., 5., 2., 4., 6.);
  a = a.Transpose();
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(CalcComplements, Test_1) {
  S21Matrix a(4, 4), c(4, 4);
  a.S21insertValues(16, 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 1., 1., 13.,
                    14., 1., 1.);
  c.S21insertValues(16, -4., 4., -28., 24., 4., -4., 12., -8., -52., 48., 60.,
                    -56., 36., -32., -44., 40.);
  a = a.CalcComplements();
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(CalcComplements, Test_2) {
  S21Matrix a(1, 1), c(1, 1);
  c.S21insertValues(1, 1.);
  a = c.CalcComplements();
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(CalcComplements, Test_3) {
  S21Matrix a(3, 4);
  EXPECT_ANY_THROW({ a.CalcComplements(); });
}

TEST(Determinant, Test_1) {
  S21Matrix a(1, 1);
  a.S21insertValues(1, 1.);
  double determinant = a.Determinant();
  EXPECT_DOUBLE_EQ(determinant, 1.);
}

TEST(Determinant, Test_2) {
  S21Matrix a(3, 4);
  EXPECT_ANY_THROW({ a.Determinant(); });
}

TEST(InverseMatrix, Test_1) {
  S21Matrix a, c;
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 1.);
  c.S21insertValues(9, (-43. / 24.), (11. / 12.), (-1. / 8.), (19. / 12.),
                    (-5. / 6.), (1. / 4.), (-1. / 8.), (1. / 4.), (-1. / 8.));
  a = a.InverseMatrix();
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(InverseMatrix, Test_2) {
  S21Matrix a;
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  EXPECT_ANY_THROW({ a.InverseMatrix(); });
}

TEST(InverseMatrix, Test_3) {
  S21Matrix a(1, 1);
  S21Matrix c(1, 1);
  a.S21insertValues(1, 1.);
  c.S21insertValues(1, 1.);
  a = a.InverseMatrix();
  EXPECT_TRUE(a.EqMatrix(c));
}

TEST(Index, Test_1) {
  S21Matrix a;
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  EXPECT_DOUBLE_EQ(a(0, 0), 1.);
  EXPECT_ANY_THROW({ a(3, 2); });
  EXPECT_ANY_THROW({ a(2, 3); });
}

TEST(Index2, Test_1) {
  S21Matrix a;
  a.S21insertValues(1, 1.);
  EXPECT_ANY_THROW({ a(3, 2); });
}

TEST(Index2, Test_2) {
  S21Matrix a;
  a.S21insertValues(1, 1.);
  const S21Matrix b(a);
  EXPECT_ANY_THROW({ b(3, 2); });
  EXPECT_DOUBLE_EQ(b(0, 0), 1.);
}

TEST(GetRows, Test_1) {
  S21Matrix a(2, 2);
  EXPECT_EQ(a.GetRows(), 2);
}

TEST(GetCols, Test_1) {
  S21Matrix a(2, 2);
  EXPECT_EQ(a.GetCols(), 2);
}

TEST(SetCols, Test_1) {
  S21Matrix a, c(3, 2), d(3, 3);
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  c.S21insertValues(9, 1., 2., 4., 5., 7., 8.);
  a.SetCols(2);
  EXPECT_TRUE(a == c);
  EXPECT_EQ(a.GetCols(), 2);
  a.SetCols(3);
  d.S21insertValues(9, 1., 2., 0., 4., 5., 0., 7., 8., 0.);
  EXPECT_TRUE(a == d);
  EXPECT_EQ(a.GetCols(), 3);
}

TEST(SetCols, Test_2) {
  S21Matrix a;
  EXPECT_ANY_THROW(a.SetCols(-1));
}

TEST(SetRows, Test_1) {
  S21Matrix a(3, 3), c(2, 3), d(3, 3);
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  c.S21insertValues(9, 1., 2., 3., 4., 5., 6.);
  a.SetRows(2);
  EXPECT_TRUE(a == c);
  EXPECT_EQ(a.GetRows(), 2);

  a.SetRows(3);
  d.S21insertValues(9, 1., 2., 3., 4., 5., 6., 0., 0., 0.);
  EXPECT_TRUE(a == d);
  EXPECT_EQ(a.GetRows(), 3);
}

TEST(SetRows, Test_2) {
  S21Matrix a;
  EXPECT_ANY_THROW(a.SetRows(-1));
}

TEST(Operator_Eq, Test_1) {
  S21Matrix a;
  EXPECT_NO_THROW(a = a);
}

TEST(Operator_Mo, Test_1) {
  S21Matrix a;
  EXPECT_NO_THROW(a = std::move(a));
}

TEST(ConstructorMove, Test_1) {
  S21Matrix a;
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  S21Matrix c(a);
  S21Matrix b = (S21Matrix &&) a;
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_TRUE(b.EqMatrix(c));
}

TEST(ConstructorMove, Test_3) {
  S21Matrix a;
  a.S21insertValues(9, 1., 2., 3., 4., 5., 6., 7., 8., 9.);
  S21Matrix c(a);
  const S21Matrix b = (S21Matrix &&) a;
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_TRUE(b.EqMatrix(c));
}

TEST(Constructor, Test_1) { EXPECT_ANY_THROW(S21Matrix a(90, -1)); }

TEST(Operator_Breaks, Test_1) { EXPECT_ANY_THROW(S21Matrix a(-1, 0)); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
