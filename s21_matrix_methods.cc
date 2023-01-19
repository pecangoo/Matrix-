#include <stdio.h>

#include "s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix &o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] + o.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] - o.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &o) const {
  if (this->cols_ != o.cols_ || this->rows_ != o.rows_)
    return false;
  for (int i = 0; i < rows_; i++) {
    for (int k = 0; k < cols_; k++) {
      if (fabs((matrix_[i][k] - o.matrix_[i][k])) > 1e-6)
        return false;
    }
  }
  return true;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      this->matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  // Создаем временную матрицу С путем копироввания матрицы А
  S21Matrix temp(this->rows_, other.cols_);
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < other.cols_; n++) {
      temp.matrix_[m][n] = 0;
      for (int k = 0; k < this->cols_; k++) {
        temp.matrix_[m][n] += this->matrix_[m][k] * other.matrix_[k][n];
      }
    }
  }
  *this = temp;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix obj(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      obj.matrix_[j][i] = this->matrix_[i][j];
  return obj;
}

double S21Matrix::Determinant() const {
  double det = 0;
  // Проверка на квадратность матрицы
  // Так же проверка на единичную матрицу
  if (this->rows_ != this->cols_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  int size_matrix = this->rows_;
  if (size_matrix == 1) {
    det = this->matrix_[0][0];
  } else if (size_matrix == 2) {
    det = this->matrix_[0][0] * this->matrix_[1][1] -
          this->matrix_[1][0] * this->matrix_[0][1];
  } else if (size_matrix > 2) {
    for (int i = 0; i < this->rows_; i++) {
      S21Matrix Temp_Matrix(this->rows_ - 1, this->cols_ - 1);
      get_matrix(*this, &Temp_Matrix, i, 0);
      double d = 0;
      d = Temp_Matrix.Determinant();
      det += (this->matrix_[i][0] * d) * pow(-1, i + 2);
    }
  }
  return det;
}

void S21Matrix::get_matrix(S21Matrix A, S21Matrix *New, int skip_row,
                           int skip_column) const {
  int in = 0, jn = 0;
  for (int i = 0; i < A.rows_; i++) {
    if (i != skip_row) {
      for (int j = 0; j < A.cols_; j++) {
        if (j != skip_column) {
          New->matrix_[in][jn] = A.matrix_[i][j];
          jn++;
        }
      }
      in++;
      jn = 0;
    }
  }
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = this->Determinant();
  S21Matrix ResultMatrix(this->rows_, this->cols_);
  if (fabs(det) < 1e-6)
    throw std::out_of_range("InverseMatrix: Determinant equal zero.");
  if (this->cols_ == 1) {
    ResultMatrix.matrix_[0][0] = 1 / this->matrix_[0][0];
  } else {
    S21Matrix Temp_Matrix(this->rows_, this->cols_);
    S21Matrix Temp_Matrix2(this->rows_, this->cols_);
    Temp_Matrix = this->Transpose();
    Temp_Matrix2 = Temp_Matrix.CalcComplements();
    det = 1.0 / det;
    Temp_Matrix2.MulNumber(det);
    ResultMatrix = Temp_Matrix2;
  }
  return ResultMatrix;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (this->rows_ != this->cols_) {
    throw std::out_of_range("Incorrect matrix for CalcComplements foo.");
  }
  S21Matrix ResultMatrix(this->cols_, this->rows_);
  if (this->rows_ == 1) {
    ResultMatrix.matrix_[0][0] = 1.;
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        S21Matrix Temp_Matrix(this->rows_ - 1, this->cols_ - 1);
        this->get_matrix(*this, &Temp_Matrix, i, j);
        double det = Temp_Matrix.Determinant();
        ResultMatrix.matrix_[i][j] = det;
      }
    }
    ResultMatrix.AlgebraicAdditions();
  }
  return ResultMatrix;
}

void S21Matrix::AlgebraicAdditions() {
  // Добавляет алгебраические дополнения к матрицы
  for (int i = 0; i < this->rows_; i++)
    for (int j = 0; j < this->cols_; j++)
      this->matrix_[i][j] = this->matrix_[i][j] * pow(-1, (i + j));
}
