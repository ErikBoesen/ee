#include <iostream>
#include <cmath>
#include <cstdlib>

#define POINTS 500

int main() {
	// Create training set for teaching the network how to operate on numbers.
	for (int i = 0; i < POINTS; ++i) {
		int a = (int)(2.0 * rand() / double(RAND_MAX));
		int b = (int)(2.0 * rand() / double(RAND_MAX));
		int o = a ^ b;
		std::cout << "input: " << a << " " << b << std::endl;
		std::cout << "output: " << o << " " << std::endl;
	}
}
