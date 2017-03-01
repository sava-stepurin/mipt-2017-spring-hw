
#ifndef MIPT_2017_SPRING_HW_MATRIX_H
#define MIPT_2017_SPRING_HW_MATRIX_H

#include <cstdlib>
#include <iostream>
typedef int matrix_cell;

class Matrix {
private:
	size_t row_count;
	size_t col_count;
	matrix_cell** values;
	friend bool right_size_sum(Matrix &, Matrix &);
	friend bool right_size_mult(Matrix &, Matrix &);
public:
	Matrix(size_t, size_t);
	Matrix(const Matrix &);
	~Matrix();

	matrix_cell get(size_t, size_t) const;
	void set(size_t, size_t, matrix_cell);
	friend std::ostream &operator<<(std::ostream &, Matrix &);
	friend std::istream &operator >> (std::istream &, Matrix &);
	friend Matrix operator+(Matrix &, Matrix &);
	friend Matrix operator+(Matrix &, int);
	friend Matrix operator+(int, Matrix &);
	friend Matrix operator*(Matrix &, Matrix &);
	friend Matrix operator*(Matrix &, int);
	friend Matrix operator*(int, Matrix &);
	Matrix &operator=(const Matrix &);
	static Matrix diag(size_t, int, ...);
	static Matrix eye(size_t);
	static Matrix reverse_eye(size_t);
};

#endif //MIPT_2017_SPRING_HW_MATRIX_H
