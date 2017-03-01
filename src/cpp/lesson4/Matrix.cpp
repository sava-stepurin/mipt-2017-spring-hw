#include "matrix.h"
#include <cstring>

bool right_size_sum(Matrix &a, Matrix &b) {
	return (a.col_count == b.col_count && a.row_count == b.row_count);
}

bool right_size_mult(Matrix &a, Matrix &b) {
	return (a.col_count == b.row_count);
}

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

Matrix operator+(Matrix &a, Matrix &b) {
	if (right_size_sum(a, b)) {
		Matrix result(a.row_count, a.col_count);
		for (int row = 0; row < a.row_count; ++row) {
			for (int col = 0; col < a.col_count; ++col) {
				result.values[row][col] = a.values[row][col] + b.values[row][col];
			}
		}
		return result;
	}
	else {
		std::cout << "wrong size: " << std::endl;
		return b;
	}
}

Matrix operator+(Matrix &a, int k) {
	Matrix result(a.row_count, a.col_count);
	for (int row = 0; row < result.row_count; ++row) {
		for (int col = 0; col < result.col_count; ++col) {
			result.values[row][col] = a.values[row][col] + k;
		}
	}
	return result;
}

Matrix operator+(int k, Matrix &a) {
	return a + k;
}

Matrix operator*(Matrix &a, Matrix &b) {
	if (right_size_mult(a, b)) {
		Matrix result(a.row_count, b.col_count);
		for (int row = 0; row < a.row_count; ++row) {
			for (int col = 0; col < b.col_count; ++col) {
				result.values[row][col] = 0;
				for (int i = 0; i < a.col_count; i++) {
					result.values[row][col] += a.values[row][i] * b.values[i][col];
				}
			}
		}
		return result;
	}
	else {
		std::cout << "wrong size: " << std::endl;
		return b;
	}
}

Matrix operator*(Matrix &a, int k) {
	Matrix result(a.row_count, a.col_count);
	for (int row = 0; row < result.row_count; ++row) {
		for (int col = 0; col < result.col_count; ++col) {
			result.values[row][col] = a.values[row][col] * k;
		}
	}
	return result;
}

Matrix operator*(int k, Matrix &b) {
	return b * k;
}

Matrix &Matrix::operator=(const Matrix &m) {
	for (int i = 0; i < this->row_count; i++) {
		delete[]this->values[i];
	}
	delete[]this->values;
	this->row_count = m.row_count;
	this->col_count = m.col_count;
	this->values = new matrix_cell*[this->row_count];
	for (int i = 0; i < this->row_count; i++) {
		this->values[i] = new matrix_cell[this->col_count];
		std::memcpy(this->values[i], m.values[i], col_count * sizeof(matrix_cell));
	}
	return *this;
}

Matrix Matrix::diag(size_t size, int value1, ...) {
	Matrix result(size, size);
	int *p = &value1;
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			result.values[row][col] = (col == row) * (*p);
		}
		p++;
	}
	return result;
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

Matrix Matrix::reverse_eye(size_t count) {
	Matrix result(count, count);
	for (int row = 0; row < count; ++row) {
		for (int col = 0; col < count; ++col) {
			result.values[row][col] = (count - col - 1 == row);
		}
	}
	return result;
}