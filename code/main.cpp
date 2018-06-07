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
#define PRECISION 2

using namespace std;

void print_vector(vector<double> &v) {
	cout << '[';
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i != v.size() - 1) cout << " ";
	}
	cout << ']';
}

void print_ngram(vector<double> &v) {
	// TODO: Clean up rounding mess
	// TODO: Clean up your own mess too, let's be real
	cout << '"';
	char c;
	for (int i = 0; i < v.size(); c = (char)round(v[++i])) {
		if (c == '\n') cout << "\\n";
		else cout << c;
	}
	cout << '"';
}
void print_error(vector<double> &a, vector<double> &b) {
	cout << '[';
	cout << setprecision(PRECISION);
	for (int i = 0; i < a.size(); ++i) {
		cout << b[i] - a[i];
		if (i != a.size() - 1) cout << " ";
	}
	cout << setprecision(0);
	cout << ']';
}

int main() {
	string languages[NUM_LANGS] = {"Java", "C", "C++", "Python", "C-sharp", "Visual-Basic-.NET", "PHP", "JavaScript", "SQL", "Ruby"};

	// You wouldn't know it, but I spent a solid hour trying to get the below three lines exactly right.
	Reader *readers[NUM_LANGS];
	for (int lang_ind = 0; lang_ind < NUM_LANGS; ++lang_ind)
		readers[lang_ind] = new Reader(languages[lang_ind]);

	vector<int> topology;
	topology.push_back(N); // Input Layer
	topology.push_back(8); // (Hidden Layer)
	topology.push_back(9); // (Hidden Layer)
	topology.push_back(9); // (Hidden Layer)
	topology.push_back(NUM_LANGS); // Output Layer

	Net network(topology);

	vector<double> ngram, targets, results;

	// Trim decimals
	cout << fixed << setprecision(0);

	for (int epoch = 0; epoch < TRAINING_EPOCHS; ++epoch) {
		for (int lang_ind = 0; lang_ind < NUM_LANGS; ++lang_ind) {
			// Get new input data and feed it forward
			readers[lang_ind]->get_ngram(ngram);

			network.feed_forward(ngram);

			// Collect the network's results
			network.get_results(results);

			// Generate correct outputs
			//reader.get_outputs(targets);
			targets.clear();
			for (int field = 0; field < NUM_LANGS; ++field) targets.push_back(0);
			targets[lang_ind] = 1;
			assert(targets.size() == topology.back());

			// Backpropogate!
			network.backpropogate(targets);

			cout << "\033[36mE" << epoch << " (" << languages[lang_ind] << ',' << lang_ind << ") / \033[33m";
			print_ngram(ngram);
			cout << "\033[0m > \033[32m";
			cout << setprecision(PRECISION);
			print_vector(results);
			cout << " \033[31merr";
			print_error(results, targets);
			cout << endl;
		}
	}

	// Isn't it gorgeous?
	for (Reader *r : readers) delete r;
}
