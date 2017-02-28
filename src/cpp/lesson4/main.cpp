#include "matrix.h"

int main() {
	Matrix m(2, 2);
	Matrix n(2, 2);
	std::cin >> m;
	std::cin >> n;
	std::cout << std::endl;
	m.set(1, 0, 1);
	std::cout << m << std::endl;
	std::cout << n << std::endl;
	std::cout << m + n + m << std::endl;
	std::cout << m * n << std::endl;
	std::cout << 3 + m << std::endl;
	std::cout << Matrix::eye(3);
	return 0;
}