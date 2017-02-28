#include "matrix.h"
#include <cstring>

Matrix::Matrix(const Matrix &m) {
	this->row_count = m.row_count;
	this->col_count = m.col_count;
	this->values = new matrix_cell*[this->row_count];
	for (int i = 0; i < this->row_count; i++) {
		this->values[i] = new matrix_cell[this->col_count];
		std::memcpy(this->values[i], m.values[i], col_count * sizeof(matrix_cell));
	}
}

Matrix::Matrix(size_t row_count, size_t col_count) : row_count(row_count), col_count(col_count) {
	this->values = new matrix_cell*[this->row_count];
	for (int i = 0; i < this->row_count; i++) {
		this->values[i] = new matrix_cell[this->col_count];
	}
}

Matrix::~Matrix() {
	for (int i = 0; i < this->row_count; i++) {
		delete[]this->values[i];
	}
	delete[]this->values;
}

matrix_cell Matrix::get(size_t row, size_t col) const {
	return this->values[row][col];
}

void Matrix::set(size_t row, size_t col, matrix_cell value) {
	this->values[row][col] = value;
}

std::ostream &operator<<(std::ostream &out, Matrix &matrix) {
	for (int row = 0; row < matrix.row_count; row++) {
		for (int col = 0; col < matrix.col_count; col++) {
			out << matrix.values[row][col] << ' ';
		}
		out << std::endl;
	}
	return out;
}

std::istream &operator >> (std::istream &in, Matrix &matrix) {
	for (int row = 0; row < matrix.row_count; row++) {
		for (int col = 0; col < matrix.col_count; col++) {
			in >> matrix.values[row][col];
		}
	}
	return in;
}

Matrix Matrix::eye(size_t count) {
	Matrix result(count, count);
	for (int row = 0; row < count; ++row) {
		for (int col = 0; col < count; ++col) {
			result.values[row][col] = (col == row);
		}
	}
	return result;
}

Matrix operator+(Matrix &a, Matrix &b) {
	Matrix result(a.row_count, a.col_count);
	for (int row = 0; row < a.row_count; ++row) {
		for (int col = 0; col < a.col_count; ++col) {
			result.values[row][col] = a.values[row][col] + b.values[row][col];
		}
	}
	return result;
}

Matrix operator*(Matrix &a, Matrix &b) {
	Matrix result(a.row_count, b.col_count);
	int row = 0;
	int col = 0;
	for (int row = 0; row < result.row_count; ++row) {
		for (int col = 0; col < result.col_count; ++col) {
			result.values[row][col] = 0;
			for (int i = 0; i < a.col_count; ++i) {
				result.values[row][col] += a.values[row][i] * b.values[i][col];
			}
		}
	}
	return result;
}

Matrix operator+(int k, Matrix &m) {
	Matrix result(m.row_count, m.col_count);
	for (int row = 0; row < m.row_count; ++row) {
		for (int col = 0; col < m.col_count; ++col) {
			result.values[row][col] = m.values[row][col] + k;
		}
	}
	return result;
}