#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <cmath>
#include "net.hpp"
#include "reader.hpp"

#define N 8 // Length of n-grams
#define NUM_LANGS 10
#define TRAINING_EPOCHS 10 // TODO: MAKE MORE BIGLY (┛◉Д◉)┛

using namespace std;


void print_ngram(vector<double> &v) {
	for (int i = 0; i < v.size(); ++i) cout << (char)round(v[i]);
}
void print_vector(vector<double> &v) {
	cout << '[';
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i != v.size() - 1) cout << " ";
	}
	cout << ']';
}
void print_error(vector<double> &a, vector<double> &b) {
	cout << '[';
	cout << setprecision(4);
	for (int i = 0; i < a.size(); ++i) {
		cout << b[i] - a[i];
		if (i != a.size() - 1) cout << " ";
	}
	cout << setprecision(0);
	cout << ']';
}


int main() {
	string languages[NUM_LANGS] = {"Java", "C", "C++", "Python", "C-sharp", "Visual-Basic-.NET", "PHP", "JavaScript", "SQL", "Ruby"};

	vector<double> ngram;
	Reader *readers[NUM_LANGS];
	for (int lang_ind = 0; lang_ind < NUM_LANGS; lang_ind++) {
		readers[lang_ind] = new Reader(languages[lang_ind]);
		readers[0]->get_ngram(ngram); print_ngram(ngram);
	}
	readers[0]->get_ngram(ngram); print_ngram(ngram);

	vector<int> topology;
	topology.push_back(N); // Input Layer
	topology.push_back(8); // (Hidden Layer)
	topology.push_back(9); // (Hidden Layer)
	topology.push_back(9); // (Hidden Layer)
	topology.push_back(NUM_LANGS); // Output Layer

	readers[5]->get_ngram(ngram);
	print_ngram(ngram);

	for (Reader *r : readers) delete r;
}
