#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include "net.h"

using namespace std;

void Net::get_results(vector<double> &results) const {
	results.clear();

	for (int n = 0; n < this->layers.back().size() - 1; ++n) {
		results.push_back(this->layers.back()[n].get_output());
	}
}

void Net::backpropogate(const std::vector<double> &targets) {
	// Get total net error
	Layer &output_layer = this->layers.back();
	this->error = 0.0;

	for (int n = 0; n < output_layer.size() - 1; ++n) {
		double delta = targets[n] - output_layer[n].get_output();
		this->error += delta * delta;
	}
	this->error = sqrt(this->error / (output_layer.size() - 1));

	// Calculate gradients for output layer
	for (int n = 0; n < output_layer.size() - 1; ++n) {
		output_layer[n].calculate_output_gradients(targets[n]);
	}

	// Calculate gradients on hidden layers
	for (int layer_num = this->layers.size() - 2; layer_num > 0; --layer_num) {
		for (int n = 0; n < this->layers[layer_num].size(); ++n)
			this->layers[layer_num][n].calculate_hidden_gradients(this->layers[layer_num + 1]);
	}
	// Update synapse weights for all layers except input
	// TODO: Make sure this is what it's doing
	for (int layer_num = this->layers.size() - 1; layer_num > 0; --layer_num) {
		for (int n = 0; n < this->layers[layer_num].size() - 1; ++n)
			this->layers[layer_num][n].update_input_weights(this->layers[layer_num - 1]);
	}
}

void Net::feed_forward(const vector<double> &inputs) {
	// Ensure that input is the proper length to fit into our input neurons
	assert(inputs.size() == this->layers[0].size() - 1);

	// Latch the input values into the input neurons
	for (int i = 0; i < inputs.size(); ++i){
		this->layers[0][i].set_output(inputs[i]);
	}

	// Forward propagate
	for (int layer_num = 1; layer_num < this->layers.size(); ++layer_num){
		Layer &previous_layer = this->layers[layer_num - 1];
		for (int n = 0; n < this->layers[layer_num].size() - 1; ++n){
			this->layers[layer_num][n].feed_forward(previous_layer);
		}
	}
}
Net::Net(const vector<int> &topology) {
	for (int layer_num = 0; layer_num < topology.size(); ++layer_num) {
		// Create new layer
		Layer layer;

		// If we're on the last layer, there aren't any outputs
		int num_outputs = layer_num == topology.size() - 1 ? 0 : topology[layer_num + 1];

		// Fill layer with neurons, excluding bias
		for (int neuron_num = 0; neuron_num < topology[layer_num]; ++neuron_num) {
			cout << "Making neuron at (" << layer_num << "," << neuron_num << ")" << endl;
			layer.push_back(Neuron(num_outputs, neuron_num));
		}

		// TODO: No need to make bias neuron for output layer
		cout << "Making bias neuron for layer " << layer_num << endl;
		Neuron bias_neuron = Neuron(num_outputs, topology[layer_num]);
		bias_neuron.set_output(-1.0);
		layer.push_back(bias_neuron);

		this->layers.push_back(layer);
	}
}
