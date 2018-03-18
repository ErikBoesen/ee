#include <iostream>
#include <cmath>
#include <cstdlib>

#define POINTS 500

int main() {
	// Create training set for teaching the network how to OR numbers.
	for (int i = 0; i < POINTS; ++i) {
		int n1 = (int)(2.0 * rand() / double(RAND_MAX));
		int n2 = (int)(2.0 * rand() / double(RAND_MAX));
		int t = n1 ^ n2; // should be 0 or 1
		std::cout << "input: " << n1 << ".0 " << n2 << ".0 " << std::endl;
		std::cout << "output: " << t << ".0" << std::endl;
	}
}
