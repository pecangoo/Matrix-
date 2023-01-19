#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++)
    matrix_[i] = new double[cols_]();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw std::out_of_range("Rows or Cols < 0");
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++)
    matrix_[i] = new double[cols_]();
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++)
    delete[] matrix_[i];
  delete[] matrix_;
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++)
    matrix_[i] = new double[cols_]();
  for (int i = 0; i < rows_; i++)
    for (int k = 0; k < cols_; k++)
      this->matrix_[i][k] = other.matrix_[i][k];
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  if (this != &other) {
    other.cols_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
  }
}
