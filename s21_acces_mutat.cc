#include "s21_matrix_oop.h"

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0)
    throw std::out_of_range("SetRows: rows less or equal zero");
  S21Matrix temp(rows, cols_);
  for (int i = 0; i < temp.rows_; i++) {
    for (int j = 0; j < temp.cols_; j++) {
      if (i < rows_) {
        temp.matrix_[i][j] = this->matrix_[i][j];
      } else {
        temp.matrix_[i][j] = 0;
      }
    }
  }
  (*this) = temp;
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0)
    throw std::out_of_range("SetCols: cols less or equal zero");
  S21Matrix temp(rows_, cols);
  for (int i = 0; i < temp.rows_; i++) {
    for (int j = 0; j < temp.cols_; j++) {
      if (j < cols_) {
        temp.matrix_[i][j] = matrix_[i][j];
      } else {
        temp.matrix_[i][j] = 0;
      }
    }
  }
  (*this) = temp;
}
