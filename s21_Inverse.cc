#include <stdarg.h>

#include "s21_matrix_oop.h"

void S21Matrix::S21insertValues(int n, ...) {
  va_list arg_list;
  va_start(arg_list, n);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i * cols_ + j < n) {
        this->matrix_[i][j] = va_arg(arg_list, double);
      } else {
        this->matrix_[i][j] = 0;
      }
    }
  }
  va_end(arg_list);
}

// тесты на скобки
// тесты на = для одного объекты