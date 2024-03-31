#include "DL_matrix_oop.h"

// Constructors

DLMatrix::DLMatrix() {
  rows_ = 3;
  cols_ = 3;

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i)
    matrix_[i] = new double[cols_]();  // () - initializes array with zeroes
}

DLMatrix::DLMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows > 0 && cols > 0) {
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i)
      matrix_[i] = new double[cols_]();  // () - initializes array with zeroes
  } else
    throw std::invalid_argument("Rows and Columns can't be less or equal 0!");
}

DLMatrix::~DLMatrix() {
  if (nullptr != matrix_) {
    for (int i = 0; i < rows_; i++)
      if (nullptr != matrix_[i]) delete[] matrix_[i];
    delete[] matrix_;
    matrix_ = nullptr;
  }

  rows_ = 0;
  cols_ = 0;
}

DLMatrix::DLMatrix(const DLMatrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
  }
}

DLMatrix::DLMatrix(DLMatrix&& other)
    : rows_(other.rows_), cols_(other.cols_) {
  this->matrix_ = std::move(other.matrix_);
  other.matrix_ = nullptr;
}

// Methods

// Logical methods

bool DLMatrix::EqMatrix(const DLMatrix& other) noexcept {
  bool ret_val = false;

  if (DL_eq_rac(this, &other)) {
    ret_val = true;

    for (int i = 0; i < rows_ && ret_val; i++) {
      for (int j = 0; j < cols_ && ret_val; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1E-7) ret_val = false;
      }
    }
  }

  return ret_val;
}

bool DL_eq_rac(DLMatrix const* const A, DLMatrix const* const B) {
  bool ret_val = false;

  if (A->rows_ == B->rows_ && A->cols_ == B->cols_) ret_val = true;

  return ret_val;
}

// Accessors

int DLMatrix::GetRows() noexcept { return this->rows_; }

int DLMatrix::GetCols() noexcept { return this->cols_; }

// Arithmetic methods

void DLMatrix::SumMatrix(const DLMatrix& other) {
  if (nullptr == matrix_ || nullptr == other.matrix_)
    throw std::runtime_error("Matrixes aren't initialized.");
  else if (DL_eq_rac(this, &other)) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } else
    throw std::domain_error("Both matrixes must be same size.");
}

void DLMatrix::SubMatrix(const DLMatrix& other) {
  if (nullptr == matrix_ || nullptr == other.matrix_)
    throw std::runtime_error("Matrixes aren't initialized.");
  else if (DL_eq_rac(this, &other)) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  } else
    throw std::domain_error("Both matrixes must be same size.");
}

void DLMatrix::MulNumber(const double num) {
  if (nullptr == matrix_)
    throw std::runtime_error("Matrixes aren't initialized.");
  else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] *= num;
      }
    }
  }
}

void DLMatrix::MulMatrix(const DLMatrix& other) {
  if (nullptr == matrix_ || nullptr == other.matrix_)
    throw std::runtime_error("Matrixes aren't initialized.");
  else if (cols_ == other.rows_) {
    DLMatrix buf_matrix(rows_, other.cols_);
    double** p_buf_double = matrix_;

    buf_matrix.cols_ = cols_;
    cols_ = other.cols_;

    matrix_ = buf_matrix.matrix_;
    buf_matrix.matrix_ = p_buf_double;
    p_buf_double =
        nullptr;  // Возможно тоже самое делает 'buf_matrix = std::move(this);',
                  // но я не уверен, что происходит именно обмен.

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        for (int k = 0; k < buf_matrix.cols_; k++)
          matrix_[i][j] += buf_matrix.matrix_[i][k] * other.matrix_[k][j];
      }
    }
  } else
    throw std::domain_error(
        "Columns of multiplicand matrix must be the same as rows of multiplier "
        "matrix.");
}

DLMatrix DLMatrix::Transpose() {
  DLMatrix transposed_matrix(cols_, rows_);

  if (nullptr == matrix_)
    throw std::runtime_error("Matrixes aren't initialized.");
  else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        transposed_matrix.matrix_[j][i] = matrix_[i][j];
      }
    }
  }

  return transposed_matrix;
}

// // Формирует матрицу размером на 1 и 1 меньше, чем A;
// // заполняет содержимым матр. A, за исключением указанного строки и столбца.
DLMatrix DL_pre_minor_calc(DLMatrix const* const A, int row,
                             int cols) noexcept {
  DLMatrix result(A->rows_ - 1, A->cols_ - 1);
  for (int i = 0, res_rows = 0; i < A->rows_; ++i) {
    if (i != row) {
      for (int j = 0, res_cols = 0; j < A->cols_; ++j) {
        if (j != cols) {
          result.matrix_[res_rows][res_cols] = A->matrix_[i][j];
          res_cols += 1;
        }
      }
      res_rows += 1;
    }
  }

  return result;
}

double DL_recursive_det(DLMatrix* A) noexcept {
  double ret_val = 0.0;
  if (A->rows_ == 2)
    ret_val = A->matrix_[0][0] * A->matrix_[1][1] -
              A->matrix_[0][1] * A->matrix_[1][0];
  else if (A->rows_ == 1)
    ret_val = A->matrix_[0][0];
  else {
    for (int j = 0; j < A->cols_; ++j) {
      DLMatrix buf_matrix = DL_pre_minor_calc(A, 0, j);
      if ((j + 1) % 2 == 1)
        ret_val += A->matrix_[0][j] * DL_recursive_det(&buf_matrix);
      else
        ret_val -= A->matrix_[0][j] * DL_recursive_det(&buf_matrix);
    }
  }

  return ret_val;
}

double DLMatrix::Determinant() {
  double result = 0.0;

  DLMatrix Copy_matrix(*this);

  if (nullptr == matrix_)
    throw std::runtime_error("Matrixes aren't initialized.");
  else if (rows_ == cols_) {
    result = DL_recursive_det(&Copy_matrix);
  } else
    throw std::domain_error("Columns and rows aren't equal!");

  return result;
}

double DLMatrix::Minor(int i, int j) {
  DLMatrix buf_matrix = DL_pre_minor_calc(this, i, j);

  return buf_matrix.Determinant();
}

DLMatrix DLMatrix::CalcComplements() {
  DLMatrix result(rows_, cols_);

  if (nullptr == matrix_)
    throw std::runtime_error("Matrixes aren't initialized.");
  else if (rows_ == cols_) {
    for (int i = 0; i < result.rows_; ++i) {
      for (int j = 0; j < result.cols_; ++j) {
        if ((i + j) % 2 == 0)
          result.matrix_[i][j] = this->Minor(i, j);
        else
          result.matrix_[i][j] = -1 * this->Minor(i, j);
      }
    }
  } else
    throw std::domain_error("Columns and rows aren't equal!");

  return result;
}

DLMatrix DLMatrix::InverseMatrix() {
  DLMatrix result;
  if (nullptr == matrix_)
    throw std::runtime_error("Matrixes aren't initialized.");
  else if (rows_ == cols_) {
    double matrix_det = this->Determinant();

    if (matrix_det != 0 && rows_ != 1) {
      result = this->CalcComplements();
      result = result.Transpose();

      result.MulNumber(1.0 / matrix_det);
    } else if (matrix_det != 0)
      result.matrix_[0][0] = 1 / matrix_det;
    else
      throw std::domain_error("Matrix determinant equals 0!");
  } else
    throw std::domain_error("Columns and rows aren't equal!");

  return result;
}

// Mutators

void DLMatrix::SetRows(int rows) {
  if (rows < 1) throw std::domain_error("Row cant't be less than 1.");

  DLMatrix new_allocated_memory_donor_matrix(rows, cols_);

  int choosen_rows_to_parse_matrix = (rows_ <= rows) ? rows_ : rows;

  for (int i = 0; i < choosen_rows_to_parse_matrix; ++i) {
    for (int j = 0; j < cols_; ++j) {
      new_allocated_memory_donor_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }

  double** buf_to_swap_pointers = matrix_;

  matrix_ = new_allocated_memory_donor_matrix.matrix_;
  new_allocated_memory_donor_matrix.matrix_ = buf_to_swap_pointers;
  buf_to_swap_pointers = nullptr;

  new_allocated_memory_donor_matrix.rows_ = rows_;
  rows_ = rows;
}

void DLMatrix::SetCols(int cols) {
  if (cols < 1) throw std::domain_error("Column cant't be less than 1.");

  DLMatrix new_allocated_memory_donor_matrix(rows_, cols);

  int choosen_cols_to_parse_matrix = (cols_ <= cols) ? cols_ : cols;

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < choosen_cols_to_parse_matrix; ++j) {
      new_allocated_memory_donor_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }

  double** buf_to_swap_pointers = matrix_;

  matrix_ = new_allocated_memory_donor_matrix.matrix_;
  new_allocated_memory_donor_matrix.matrix_ = buf_to_swap_pointers;
  buf_to_swap_pointers = nullptr;

  new_allocated_memory_donor_matrix.cols_ = cols_;
  cols_ = cols;
}

// Operators

DLMatrix DLMatrix::operator+(const DLMatrix& other) {
  DLMatrix result_matrix_for_return = *this;
  result_matrix_for_return.SumMatrix(other);

  return result_matrix_for_return;
}

DLMatrix& DLMatrix::operator+=(const DLMatrix& other) {
  this->SumMatrix(other);

  return *this;
}

DLMatrix DLMatrix::operator-(const DLMatrix& other) {
  DLMatrix result_matrix_for_return = *this;
  result_matrix_for_return.SubMatrix(other);

  return result_matrix_for_return;
}

DLMatrix& DLMatrix::operator-=(const DLMatrix& other) {
  this->SubMatrix(other);

  return *this;
}

bool DLMatrix::operator==(const DLMatrix& other) {
  return this->EqMatrix(other);
}

DLMatrix& DLMatrix::operator=(const DLMatrix& other) {
  if (nullptr != matrix_) {
    this->~DLMatrix();
  }
  rows_ = other.rows_;
  cols_ = other.cols_;

  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
  }

  return *this;
}

double& DLMatrix::operator()(int row, int col) {
  if (rows_ - 1 < row || row < 0 || cols_ - 1 < col || col < 0)
    throw std::range_error("Chosen rows or columns out of matrix range!");
  return matrix_[row][col];
}

DLMatrix operator*(const double num, DLMatrix& current) {
  DLMatrix result_matrix_for_return = current;
  result_matrix_for_return.MulNumber(num);

  return result_matrix_for_return;
}
DLMatrix operator*(DLMatrix& current, const double num) {
  DLMatrix result_matrix_for_return = current;
  result_matrix_for_return.MulNumber(num);

  return result_matrix_for_return;
}

DLMatrix& DLMatrix::operator*=(const double num) {
  this->MulNumber(num);

  return *this;
}
DLMatrix DLMatrix::operator*(DLMatrix& other) {
  DLMatrix result_matrix_for_return = *this;
  result_matrix_for_return.MulMatrix(other);

  return result_matrix_for_return;
}

DLMatrix& DLMatrix::operator*=(const DLMatrix& other) {
  this->MulMatrix(other);

  return *this;
}