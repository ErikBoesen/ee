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
	// TODO: Clean up your own mess
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

	Reader *readers[NUM_LANGS];
	for (int lang_ind = 0; lang_ind < NUM_LANGS; lang_ind++) {
		Reader reader(languages[lang_ind]);
		readers[lang_ind] = &reader;
	}

	vector<int> topology;
	topology.push_back(8); // Input Layer
	topology.push_back(8); // (Hidden Layer)
	topology.push_back(9); // (Hidden Layer)
	topology.push_back(9); // (Hidden Layer)
	topology.push_back(10); // Output Layer

	Net network(topology);

	vector<double> ngram, targets, results;

	// Trim decimals
	cout << fixed << setprecision(0);

	for (int epoch = 0; epoch < TRAINING_EPOCHS; ++epoch) {
		for (int lang_ind = 0; lang_ind < NUM_LANGS; ++lang_ind) {
			// Get new input data and feed it forward:
			if (readers[lang_ind]->get_ngram(ngram) != topology[0]) break;

			network.feed_forward(ngram);

			// Collect the net's actual results:
			network.get_results(results);

			// Generate correct outputs
			//reader.get_outputs(targets);
			targets.clear();
			for (int field = 0; field < NUM_LANGS; ++field) targets.push_back(0);
			targets[lang_ind] = 1;
			assert(targets.size() == topology.back());

			// Backpropogate!
			network.backpropogate(targets);

			cout << "E" << epoch << " / ";
			print_ngram(ngram);
			cout << " > ";
			cout << setprecision(4);
			print_vector(results);
			cout << setprecision(0);
			cout << " (targets ";
			print_vector(targets);
			cout << "), (error ";
			print_error(results, targets);
			cout << ")" << endl;
		}
	}
}
