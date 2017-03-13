#include "BigInt.h"

void BigInt::create(int size) {
	this->size = size / 3 + (size % 3 != 0);
	this->values = new int[this->size + 1];
	this->values[this->size] = 0;
}

void BigInt::delete_nulls() {
	int i = this->size - 1;
	while (this->values[i] == 0) {
		this->size--;
		i--;
	}
}

BigInt::BigInt(const char *values) {
	int length = strlen(values);
	create(length);
	for (int i = 0; i < this->size; i++) {
		if (length - i * 3 - 3 >= 0) {
			this->values[i] = int(values[length - i * 3 - 1]) - '0' + (int(values[length - i * 3 - 2]) - '0') * 10 + (int(values[length - i * 3 - 3]) - '0') * 100;
		}
		else if (length - i * 3 - 2 >= 0) {
			this->values[i] = int(values[length - i * 3 - 1]) - '0' + (int(values[length - i * 3 - 2]) - '0') * 10;
		}
		else {
			this->values[i] = int(values[length - i * 3 - 1]) - '0';
		}
	}
}

BigInt::BigInt(const int value) {
	int temp = value;
	int sum = 0;
	while (temp > 0) {
		temp = temp / 10;
		sum++;
	}
	create(sum);
	int number = value;
	for (int i = 0; i < this->size; i++) {
		this->values[i] = number % 1000;
		number = number / 1000;
	}
}

BigInt::BigInt(const BigInt &that) {
	this->size = that.size;
	this->values = new int[this->size + 1];
	std::memcpy(this->values, that.values, that.size * sizeof(int));
	this->values[this->size] = 0;
}

BigInt::~BigInt() {
	delete[]this->values;
}

std::ostream &operator<<(std::ostream &os, const BigInt &temp) {
	for (int i = temp.size - 1; i >= 0; i--) {
		if (temp.values[i] < 100 && i != temp.size - 1) {
			os << '0';
			if (temp.values[i] < 10) {
				os << '0';
			}
		}
		os << temp.values[i];
	}
	return os;
}

void BigInt::resize(int new_size) {
	int *temp = new int[new_size + 1];
	std::memcpy(temp, this->values, this->size * sizeof(int));
	temp[new_size] = 0;
	delete[]this->values;
	this->values = temp;
	this->size = new_size;
}

BigInt add_sum(const BigInt &a, const BigInt &b) {
	BigInt res(a);
	int rest = 0;
	int sum = 0;
	for (int i = 0; i < b.size; i++) {
		sum = res.values[i] + b.values[i];
		res.values[i] = rest + sum % 1000;
		rest = sum / 1000;
	}
	if (rest > 0) {
		res.resize(res.size + 1);
		res.values[res.size - 1] = rest;
	}
	return res;
}

BigInt operator+(const BigInt &a, const BigInt &b) {
	if (a.size > b.size) {
		return add_sum(a, b);
	}
	else {
		return add_sum(b, a);
	}
}

BigInt operator-(const BigInt &a, const BigInt &b) {
	BigInt res(a);
	int temp = 0;
	for (int i = 0; i < b.size; i++) {
		res.values[i] -= temp;
		if (res.values[i] < b.values[i]) {
			res.values[i] += 1000;
			temp = 1;
		}
		else {
			temp = 0;
		}
		res.values[i] -= b.values[i];
	}
	res.delete_nulls();
	return res;
}

BigInt add_mult(const BigInt &a, const BigInt &b) {
	BigInt res(a);
	int rest;
	int mult;
	for (int i = 0; i < b.size; i++) {
		rest = 0;
		mult = 0;
		for (int j = 0; j < a.size; j++) {
			mult = res.values[j] * b.values[i];
			if (j + i >= a.size) {
				res.resize(i + j + 1);
			}
			res.values[j + i] = (rest + mult % 1000) % 1000;
			rest = (rest + mult % 1000) / 1000 + mult / 1000;
		}
		if (rest != 0) {
			res.resize(a.size + i + 1);
			res.values[a.size + i] = rest;
		}
	}
	return res;
}

BigInt operator*(const BigInt &a, const BigInt &b) {
	if (a.size > b.size) {
		return add_mult(a, b);
	}
	else {
		return add_mult(b, a);
	}
}

BigInt operator*(const int &a, const BigInt &b) {
	BigInt temp(a);
	return temp * b;
}

BigInt operator/(const BigInt &a, const BigInt &b) {
	int div = 0;
	int temp = 1;
	for (int i = 0; i < b.size; i++) {
		div += b.values[i] * temp;
		temp *= 1000;
	}
	BigInt res(a);
	int current;
	int add = 0;
	for (int i = res.size - 1; i >= 0; i--) {
		current = res.values[i] + add * 1000;
		res.values[i] = current / div;
		add = current % div;
	}
	res.delete_nulls();
	return res;
}