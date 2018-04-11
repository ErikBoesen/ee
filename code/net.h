#pragma once
#include <vector>
#include "neuron.h"

using namespace std;

class Net {
public:
	Net(const vector<int> &topology);
	void feed_forward(const vector<double> &inputs);
	void backpropogate(const vector<double> &targets);
	void get_results(vector<double> &results) const;

private:
	vector<Layer> layers;
	double error;
};
