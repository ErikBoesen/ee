#include <vector>
#include <iostream>
#include <cassert>
#include "net.h"
#include "reader.h"

using namespace std;

void print_vector(vector<double> &v) {
	cout << '[';
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i != v.size() - 1) cout << " ";
	}
	cout << ']';
}

int main() {
	Reader reader("training_data.txt");
	vector<int> topology;
	topology.push_back(2);
	topology.push_back(4);
	topology.push_back(3);
	topology.push_back(1);

	Net network(topology);

	vector<double> inputs, targets, results;

	for (int pass = 0; !reader.isEof(); ++pass) {
		// Get new input data and feed it forward:
		if (reader.get_inputs(inputs) != topology[0]) break;

		cout << "P" << pass << " / ";
		print_vector(inputs);
		network.feed_forward(inputs);

		// Collect the net's actual results:
		network.get_results(results);
		cout << " > ";
		print_vector(results);

		// Show correct outputs
		reader.get_outputs(targets);
		assert(targets.size() == topology.back());
		cout << " (targets ";
		print_vector(targets);
		cout << "). ";

		// Backpropogate!
		network.backpropogate(targets);

		// Report how training is going.
		cout << "Recent error: " << network.get_recent_average_error() << endl;
	}
}
