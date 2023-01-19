#ifndef __SRC_S21MATRIX_H__
#define __SRC_S21MATRIX_H__
#include <cmath>
#include <iostream>
class S21Matrix {
private:
  // attributes
  int rows_, cols_;
  double **matrix_;
  void get_matrix(S21Matrix A, S21Matrix *New, int skip_row,
                  int skip_column) const;
  void AlgebraicAdditions();

public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  ~S21Matrix();
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;

  // overloads
  S21Matrix operator=(const S21Matrix &other);
  double &operator()(int row, int col);
  double operator()(int row, int col) const;
  bool operator==(const S21Matrix &other) const noexcept;
  S21Matrix &operator=(S21Matrix &&A) noexcept;

  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other) const;

  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(double number) const;
  S21Matrix friend operator*(double num, S21Matrix &other);

  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);

  // methods
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
  S21Matrix CalcComplements() const;
  // additional

  // mutators
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  // testing
  void S21insertValues(int n, ...);
};

#endif
