#ifndef __DL_MATRIX_OOP_H__
#define __DL_MATRIX_OOP_H__

#include <cmath>
#include <stdexcept>

class DLMatrix {
 private:
  int rows_, cols_;
  double** matrix_;

  double Minor(int i, int j);

 public:
  DLMatrix();                        // default constructor
  DLMatrix(int rows, int cols);      // parameterized constructor
  DLMatrix(const DLMatrix& other);  // copy constructor
  DLMatrix(DLMatrix&& other);       // move constructor
  ~DLMatrix();                       // destructor

  // some operators overloads

  DLMatrix& operator=(const DLMatrix& other);  // assignment operator overload
  double& operator()(int row, int col);          // index operator overload
  DLMatrix& operator+=(const DLMatrix& other);
  DLMatrix operator+(const DLMatrix& other);
  DLMatrix& operator-=(const DLMatrix& other);
  DLMatrix operator-(const DLMatrix& other);
  bool operator==(const DLMatrix& other);
  friend DLMatrix operator*(const double num, DLMatrix& current);
  friend DLMatrix operator*(DLMatrix& current, const double num);
  DLMatrix& operator*=(const double num);
  DLMatrix operator*(DLMatrix& other);
  DLMatrix& operator*=(const DLMatrix& other);

  // public methods

  bool EqMatrix(const DLMatrix& other) noexcept;
  void SumMatrix(const DLMatrix& other);
  void SubMatrix(const DLMatrix& other);
  void MulNumber(const double num);
  void MulMatrix(const DLMatrix& other);
  DLMatrix Transpose();
  DLMatrix CalcComplements();
  double Determinant();
  DLMatrix InverseMatrix();

  // accessors

  int GetRows() noexcept;
  int GetCols() noexcept;

  // mutators

  void SetRows(int rows);
  void SetCols(int cols);

  friend bool DL_eq_rac(DLMatrix const* const A, DLMatrix const* const B);
  friend DLMatrix DL_pre_minor_calc(DLMatrix const* const A, int row,
                                      int cols) noexcept;
  friend double DL_recursive_det(DLMatrix* A) noexcept;
};

#endif