#include "matrix.h"

int main() {
	Matrix m(2, 2);
	Matrix n(2, 2);
	std::cin >> m;
	std::cin >> n;
	Matrix f(2, 2);
	f = n;
	std::cout << f << std::endl;
	m.set(1, 0, 1);
	std::cout << m << std::endl;
	std::cout << n << std::endl;
	std::cout << m + n << std::endl;
	std::cout << m * n << std::endl;
	std::cout << m + 3 << std::endl;
	std::cout << 3 + m << std::endl;
	std::cout << m * 3 << std::endl;
	std::cout << 3 * m << std::endl;
	std::cout << Matrix::diag(4, 1, 2, 3, 6) << std::endl;
	std::cout << Matrix::eye(3) << std::endl;
	std::cout << Matrix::reverse_eye(3) << std::endl;
	system("pause");
	return 0;
}