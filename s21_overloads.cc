#include <cstring>

#include "s21_matrix_oop.h"
S21Matrix S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other)
    return *this;
  this->~S21Matrix();
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = new double *[rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
    memcpy(this->matrix_[i], other.matrix_[i], this->cols_ * sizeof(double));
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return this->EqMatrix(other);
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_)
    throw std::out_of_range("Can't sum matrix");
  S21Matrix ResultMatrix(*this);
  ResultMatrix.SumMatrix(other);
  return ResultMatrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_)
    throw std::out_of_range("Can't sub matrix");
  S21Matrix ResultMatrix(*this);
  ResultMatrix.SubMatrix(other);
  return ResultMatrix;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  if (this->cols_ != other.rows_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  S21Matrix ResultMatrix(*this);
  ResultMatrix.MulMatrix(other);
  return ResultMatrix;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix ResultMatrix(*this);
  ResultMatrix.MulNumber(num);
  return ResultMatrix;
}

S21Matrix operator*(double num, S21Matrix &other) { return other * num; }

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  if (this->cols_ != other.rows_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  this->MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this == &other)
    return *this;
  for (int i = 0; i < rows_; i++)
    delete[] matrix_[i];
  delete[] matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}

double S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}