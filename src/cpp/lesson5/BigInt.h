#include <iostream>

class BigInt {
private:
	int *values;
	int size;
	void resize(int new_size);
	friend BigInt add_sum(const BigInt &, const BigInt &);
	friend BigInt add_mult(const BigInt &, const BigInt &);
	void create(int size);
	void delete_nulls();
public:
	BigInt(const char *);
	BigInt(const int);
	BigInt(const BigInt &);
	~BigInt();
	friend std::ostream &operator<<(std::ostream &, const BigInt &);
	friend BigInt operator+(const BigInt &, const BigInt &);
	friend BigInt operator-(const BigInt &, const BigInt &);
	friend BigInt operator*(const BigInt &, const BigInt &);
	friend BigInt operator*(const int &, const BigInt &);
	friend BigInt operator/(const BigInt &, const BigInt &);
};