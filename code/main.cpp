#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include "net.hpp"
#include "reader.hpp"

using namespace std;

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
	Reader reader("training_data.txt");
	vector<int> topology;
	topology.push_back(2);
	topology.push_back(5);
	topology.push_back(3);

	Net network(topology);

	vector<double> inputs, targets, results;

	cout << fixed << setprecision(0);

	for (int epoch = 0; !reader.isEof(); ++epoch) {
		// Get new input data and feed it forward:
		if (reader.get_inputs(inputs) != topology[0]) break;

		network.feed_forward(inputs);

		// Collect the net's actual results:
		network.get_results(results);

		// Show correct outputs
		reader.get_outputs(targets);
		assert(targets.size() == topology.back());

		// Backpropogate!
		network.backpropogate(targets);

		cout << "E" << epoch << " / ";
		print_vector(inputs);
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
