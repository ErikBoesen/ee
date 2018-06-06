#include <iostream>
#include <vector>
#include <cmath>
#include "reader.hpp"

using namespace std;


void print_ngram(vector<double> &v) {
	for (int i = 0; i < v.size(); ++i) cout << (char)round(v[i]);
}

int main() {
    Reader reader("C");
    std::vector<double> ngram;
    reader.get_ngram(ngram);
    print_ngram(ngram);
}
