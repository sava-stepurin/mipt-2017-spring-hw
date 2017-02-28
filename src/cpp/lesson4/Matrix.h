
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
public:
	Matrix(size_t, size_t);
	Matrix(const Matrix &);
	~Matrix();

	matrix_cell get(size_t, size_t) const;
	void set(size_t, size_t, matrix_cell);
	friend std::ostream &operator<<(std::ostream &, Matrix &);
	friend std::istream &operator>>(std::istream &, Matrix &);
	friend Matrix operator+(Matrix &, Matrix &);
	friend Matrix operator*(Matrix &, Matrix &);
	friend Matrix operator+(int, Matrix &);
	static Matrix eye(size_t);
};

#endif //MIPT_2017_SPRING_HW_MATRIX_H
