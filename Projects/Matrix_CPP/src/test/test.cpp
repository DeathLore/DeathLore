#include "../DL_matrix_oop.h"
#include "gtest/gtest.h"

TEST(IniConstructorTest, WrongRows) {
  try {
    DLMatrix m1(0, 1);
  } catch (std::exception& wrong_rows_error) {
    const char* errors_text = wrong_rows_error.what();

    EXPECT_STREQ(errors_text, "Rows and Columns can't be less or equal 0!");
  }
}

TEST(IniConstructorTest, WrongCols) {
  try {
    DLMatrix m1(1, 0);
  } catch (std::exception& wrong_cols_error) {
    const char* errors_text = wrong_cols_error.what();

    EXPECT_STREQ(errors_text, "Rows and Columns can't be less or equal 0!");
  }
}

TEST(SelectMatrixValue, WrongParameters) {
  DLMatrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 0;
  m(1, 1) = 0;

  try {
    m(-1, 2);

  } catch (std::exception& select_error) {
    const char* errors_text = select_error.what();

    EXPECT_STREQ(errors_text, "Chosen rows or columns out of matrix range!");
  }
}

TEST(EqualTest, Equal) {
  DLMatrix m1;
  DLMatrix m2;
  EXPECT_EQ(m1.EqMatrix(m2), true);
}

TEST(EqualTest, NotEqual) {
  DLMatrix m1;
  DLMatrix m2;
  m2.SetRows(2);
  EXPECT_EQ(m1.EqMatrix(m2), false);
}

TEST(EqualTest, EqualValues) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  EXPECT_EQ(m1.EqMatrix(m2), true);
}

TEST(EqualTest, Operator) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);
  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  EXPECT_EQ(m1 == m2, true);
}

TEST(SumTest, Sum) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;

  m1.SumMatrix(m2);

  EXPECT_EQ(m1(0, 1), 2);
}

TEST(SumTest, Operator) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;

  double res = (m1 + m2)(0, 1);

  EXPECT_EQ(res, 2.0);
}

TEST(SumTest, Assignment) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;

  m1 += m2;

  EXPECT_EQ(m1(0, 1), 2.0);
}

TEST(SumTest, nullptr_error) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  try {
    m2.~DLMatrix();

    m1.SumMatrix(m2);
  } catch (std::exception& sum_error) {
    const char* errors_text = sum_error.what();

    EXPECT_STREQ(errors_text, "Matrixes aren't initialized.");
  }
}

TEST(SumTest, DifferentSizeError) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 3);

  try {
    m1.SumMatrix(m2);
  } catch (std::exception& sum_error) {
    const char* errors_text = sum_error.what();

    EXPECT_STREQ(errors_text, "Both matrixes must be same size.");
  }
}

TEST(SubTest, Sub) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;

  m1.SubMatrix(m2);

  EXPECT_EQ(m1(0, 1), 0);
}

TEST(SubTest, Operator) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;

  double res = (m1 - m2)(0, 1);

  EXPECT_EQ(res, 0);
}

TEST(SubTest, Assignment) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;

  m1 -= m2;

  EXPECT_EQ(m1(0, 1), 0);
}

TEST(SubTest, nullptr_error) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  try {
    m2.~DLMatrix();

    m1.SubMatrix(m2);
  } catch (std::exception& sub_error) {
    const char* errors_text = sub_error.what();

    EXPECT_STREQ(errors_text, "Matrixes aren't initialized.");
  }
}

TEST(SubTest, DifferentSizeError) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 3);

  try {
    m1.SubMatrix(m2);
  } catch (std::exception& sub_error) {
    const char* errors_text = sub_error.what();

    EXPECT_STREQ(errors_text, "Both matrixes must be same size.");
  }
}

TEST(MulNumberTest, MulNumber) {
  DLMatrix m(2, 2);

  m(0, 0) = 0;
  m(0, 1) = 1;
  m(1, 0) = 2;
  m(1, 1) = 3;

  m.MulNumber(2);

  EXPECT_EQ(m(1, 0), 4);
}

TEST(MulNumberTest, OperatorRight) {
  DLMatrix m(2, 2);

  m(0, 0) = 0;
  m(0, 1) = 1;
  m(1, 0) = 2;
  m(1, 1) = 3;

  double res = (m * 2)(1, 0);

  EXPECT_EQ(res, 4);
}

TEST(MulNumberTest, OperatorLeft) {
  DLMatrix m(2, 2);

  m(0, 0) = 0;
  m(0, 1) = 1;
  m(1, 0) = 2;
  m(1, 1) = 3;

  double res = (2 * m)(1, 0);

  EXPECT_EQ(res, 4);
}

TEST(MulNumberTest, Assignment) {
  DLMatrix m(2, 2);

  m(0, 0) = 0;
  m(0, 1) = 1;
  m(1, 0) = 2;
  m(1, 1) = 3;

  m *= 2;

  EXPECT_EQ(m(1, 0), 4);
}

TEST(MulNumberTest, nullptr_error) {
  DLMatrix m1(2, 2);

  try {
    m1.~DLMatrix();

    m1.MulNumber(3);
  } catch (std::exception& mul_num_error) {
    const char* errors_text = mul_num_error.what();

    EXPECT_STREQ(errors_text, "Matrixes aren't initialized.");
  }
}

TEST(MulMatrixTest, MulMatrix) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(1, 0) = 2;
  m2(1, 1) = 3;

  m1.MulMatrix(m2);

  EXPECT_EQ(m1(1, 1), 11);
}

TEST(MulMatrixTest, MulMatrixRotate) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 4);

  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(0, 2) = 0;
  m2(0, 3) = 5;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  m2(1, 2) = 5;
  m2(1, 3) = 0;

  m1.MulMatrix(m2);

  EXPECT_EQ(m1(1, 3), 10);
}

TEST(MulMatrixTest, Operator) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 4);

  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(0, 2) = 0;
  m2(0, 3) = 5;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  m2(1, 2) = 5;
  m2(1, 3) = 0;

  double res = (m1 * m2)(1, 3);

  EXPECT_EQ(res, 10);
}

TEST(MulMatrixTest, Assignment) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 4);

  m1(0, 0) = 0;
  m1(0, 1) = 1;
  m1(1, 0) = 2;
  m1(1, 1) = 3;

  m2(0, 0) = 0;
  m2(0, 1) = 1;
  m2(0, 2) = 0;
  m2(0, 3) = 5;
  m2(1, 0) = 2;
  m2(1, 1) = 3;
  m2(1, 2) = 5;
  m2(1, 3) = 0;

  m1 *= m2;

  EXPECT_EQ(m1(1, 3), 10);
}

TEST(MulMatrixTest, nullptr_error) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  try {
    m2.~DLMatrix();

    m1.MulMatrix(m2);
  } catch (std::exception& mul_matrix_error) {
    const char* errors_text = mul_matrix_error.what();

    EXPECT_STREQ(errors_text, "Matrixes aren't initialized.");
  }
}

TEST(MulMatrixTest, DifferentSizeError) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 3);

  try {
    m1.MulMatrix(m2);
  } catch (std::exception& mul_matrix_error) {
    const char* errors_text = mul_matrix_error.what();

    EXPECT_STREQ(errors_text,
                 "Columns of multiplicand matrix must be the same as rows of "
                 "multiplier matrix.");
  }
}

TEST(TransposeTest, Transpose) {
  DLMatrix m1(3, 2);
  DLMatrix m2(2, 3);

  m1(0, 0) = 1;
  m1(0, 1) = 4;
  m1(1, 0) = 2;
  m1(1, 1) = 5;
  m1(2, 0) = 3;
  m1(2, 1) = 6;

  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(0, 2) = 3;
  m2(1, 0) = 4;
  m2(1, 1) = 5;
  m2(1, 2) = 6;

  bool res = m1.Transpose() == m2;

  EXPECT_EQ(res, true);
}

TEST(ComplementsTest, ComplementsMatrix) {
  DLMatrix m1(3, 3);
  DLMatrix m2(3, 3);

  m1(0, 0) = 1;
  m1(0, 1) = 2;
  m1(0, 2) = 3;
  m1(1, 0) = 0;
  m1(1, 1) = 4;
  m1(1, 2) = 2;
  m1(2, 0) = 5;
  m1(2, 1) = 2;
  m1(2, 2) = 1;

  m2(0, 0) = 0;
  m2(0, 1) = 10;
  m2(0, 2) = -20;
  m2(1, 0) = 4;
  m2(1, 1) = -14;
  m2(1, 2) = 8;
  m2(2, 0) = -8;
  m2(2, 1) = -2;
  m2(2, 2) = 4;

  bool res = m1.CalcComplements() == m2;

  EXPECT_EQ(res, true);
}

TEST(ComplementsTest, DifferentSizeError) {
  DLMatrix m1(2, 3);

  try {
    m1.CalcComplements();
  } catch (std::exception& calc_complements__error) {
    const char* errors_text = calc_complements__error.what();

    EXPECT_STREQ(errors_text, "Columns and rows aren't equal!");
  }
}

TEST(DeterminantTest, Determinant) {
  DLMatrix m(3, 3);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;
  m(2, 0) = 7;
  m(2, 1) = 8;
  m(2, 2) = 9;

  double res = m.Determinant();

  EXPECT_EQ(res, 0);
}

TEST(DeterminantTest, OneMatr) {
  DLMatrix m(1, 1);

  m(0, 0) = 1;

  double res = m.Determinant();

  EXPECT_EQ(res, 1);
}

TEST(DeterminantTest, nullptr_error) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  try {
    m1.~DLMatrix();

    m1.Determinant();
  } catch (std::exception& determinant_error) {
    const char* errors_text = determinant_error.what();

    EXPECT_STREQ(errors_text, "Matrixes aren't initialized.");
  }
}

TEST(DeterminantTest, DifferentSizeError) {
  DLMatrix m1(2, 3);

  try {
    m1.Determinant();
  } catch (std::exception& sum_error) {
    const char* errors_text = sum_error.what();

    EXPECT_STREQ(errors_text, "Columns and rows aren't equal!");
  }
}

TEST(InverseMatrixTest, InverseMatrix) {
  DLMatrix m1(3, 3);
  DLMatrix m2(3, 3);

  m1(0, 0) = 2;
  m1(0, 1) = 5;
  m1(0, 2) = 7;
  m1(1, 0) = 6;
  m1(1, 1) = 3;
  m1(1, 2) = 4;
  m1(2, 0) = 5;
  m1(2, 1) = -2;
  m1(2, 2) = -3;

  m2(0, 0) = 1;
  m2(0, 1) = -1;
  m2(0, 2) = 1;
  m2(1, 0) = -38;
  m2(1, 1) = 41;
  m2(1, 2) = -34;
  m2(2, 0) = 27;
  m2(2, 1) = -29;
  m2(2, 2) = 24;

  bool res = m1.InverseMatrix() == m2;

  EXPECT_EQ(res, true);
}

TEST(InverseMatrixTest, OneMatr) {
  DLMatrix m(1, 1);

  m(0, 0) = 1;

  double res = m.InverseMatrix()(0, 0);

  EXPECT_EQ(res, 1);
}

TEST(InverseMatrixTest, ZeroDeterminant) {
  DLMatrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 0;
  m(1, 1) = 0;

  try {
    m.InverseMatrix();

  } catch (std::exception& inverse_error) {
    const char* errors_text = inverse_error.what();

    EXPECT_STREQ(errors_text, "Matrix determinant equals 0!");
  }
}

TEST(InverseMatrixTest, nullptr_error) {
  DLMatrix m1(2, 2);
  DLMatrix m2(2, 2);

  try {
    m1.~DLMatrix();

    m1.InverseMatrix();
  } catch (std::exception& inverse_error) {
    const char* errors_text = inverse_error.what();

    EXPECT_STREQ(errors_text, "Matrixes aren't initialized.");
  }
}

TEST(InverseMatrixTest, DifferentSizeError) {
  DLMatrix m1(2, 3);

  try {
    m1.InverseMatrix();
  } catch (std::exception& inverse_error) {
    const char* errors_text = inverse_error.what();

    EXPECT_STREQ(errors_text, "Columns and rows aren't equal!");
  }
}

TEST(AccessorTest, GetRows) {
  DLMatrix m(3, 3);
  int res = m.GetRows();
  EXPECT_EQ(res, 3);
}

TEST(AccessorTest, GetCols) {
  DLMatrix m(3, 3);
  int res = m.GetCols();
  EXPECT_EQ(res, 3);
}

TEST(CopyTest, Copy) {
  DLMatrix m1(2, 2);
  DLMatrix m2(3, 3);
  m1 = m2;
  EXPECT_EQ(m1 == m2, true);
}

TEST(MoveTest, Move) {
  DLMatrix m1(2, 2);
  DLMatrix m2 = std::move(m1);
  EXPECT_EQ(m2(0, 0), 0);
}

TEST(MutatorsTest, SetLessRows) {
  DLMatrix m(2, 2);
  m(0, 0) = 1;
  m(1, 0) = 2;
  m(0, 1) = 3;
  m(1, 1) = 4;

  m.SetRows(1);
  int rows = m.GetRows();
  EXPECT_EQ((rows == 1) && (m(0, 1) == 3), 1);
}

TEST(MutatorsTest, SetMoreRows) {
  DLMatrix m(2, 2);
  m(0, 0) = 1;
  m(1, 0) = 2;
  m(0, 1) = 3;
  m(1, 1) = 4;

  m.SetRows(3);
  int rows = m.GetRows();
  EXPECT_EQ((rows == 3) && (m(0, 1) == 3) && (m(2, 1) == 0), 1);
}

TEST(MutatorsTest, SetRowsError) {
  DLMatrix m(2, 2);
  m(0, 0) = 1;
  m(1, 0) = 2;
  m(0, 1) = 3;
  m(1, 1) = 4;

  try {
    m.SetRows(0);
  } catch (std::exception& set_row_error) {
    const char* errors_text = set_row_error.what();

    EXPECT_STREQ(errors_text, "Row cant't be less than 1.");
  }
}

TEST(MutatorsTest, SetLessCols) {
  DLMatrix m(2, 2);
  m(0, 0) = 1;
  m(1, 0) = 2;
  m(0, 1) = 3;
  m(1, 1) = 4;

  m.SetCols(1);
  int cols = m.GetCols();
  EXPECT_EQ((cols == 1) && (m(1, 0) == 2), 1);
}

TEST(MutatorsTest, SetMoreCols) {
  DLMatrix m(2, 2);
  m(0, 0) = 1;
  m(1, 0) = 2;
  m(0, 1) = 3;
  m(1, 1) = 4;

  m.SetCols(3);
  int cols = m.GetCols();
  EXPECT_EQ((cols == 3) && (m(0, 1) == 3) && (m(1, 2) == 0), 1);
}

TEST(MutatorsTest, SetColsError) {
  DLMatrix m(2, 2);
  m(0, 0) = 1;
  m(1, 0) = 2;
  m(0, 1) = 3;
  m(1, 1) = 4;

  try {
    m.SetCols(0);
  } catch (std::exception& set_col_error) {
    const char* errors_text = set_col_error.what();

    EXPECT_STREQ(errors_text, "Column cant't be less than 1.");
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}