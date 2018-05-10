#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

#define POINTS 1000

int main() {
	std::ofstream f;
	f.open("training_data.txt");
	// Create training set for teaching the network how to operate on numbers.
	for (int i = 0; i < POINTS; ++i) {
		int a = (int)(2.0 * rand() / double(RAND_MAX));
		int b = (int)(2.0 * rand() / double(RAND_MAX));
		int o_and = a & b,
			o_or  = a | b,
			o_xor = a ^ b;
		f << "input: " << a << " " << b << std::endl;
		f << "output: " << o_and << " " << o_or << " " << o_xor << std::endl;
	}
}
