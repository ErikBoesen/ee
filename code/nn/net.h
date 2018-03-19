#pragma once
#include <vector>
#include <cmath>
#include <cassert>
#define ETA 0.05 // Learning rate [0..1]
#define ALPHA 0.5 // Momentum (multiplier of last change in weight) [0..]

using namespace std;

struct Connection {
	double weight;
	double delta_weight;
};

class Neuron;

typedef vector<Neuron> Layer;

class Neuron {
public:
	Neuron(int num_outputs, int index);
	void set_output(double output) { this->output = output; }
	double get_output() const { return this->output; }
	void feed_forward(const Layer &previous_layer);
	void calculate_output_gradients(double targets);
	void calculate_hidden_gradients(const Layer &next_layer);
	void update_input_weights(Layer &previous_layer);
private:
	static double activation(double x);
	static double activation_derivative(double x);
	double sum_dow(const Layer &next_layer) const;
	double output;
	vector<Connection> output_weights;
	int index;
	double gradient;
};

void Neuron::update_input_weights(Layer &previous_layer) {
	// The weights to be updated are in the Connection container
	// in the nuerons in the preceding layer

	for (int n = 0; n < previous_layer.size(); ++n) {
		Neuron &neuron = previous_layer[n];
		double old_delta_weight = neuron.output_weights[this->index].delta_weight;

		double new_delta_weight =
				// Individual input, magnified by the gradient and train rate:
				ETA
				* neuron.get_output()
				* this->gradient
				// Also add momentum, a fraction of the previous delta weight
				+ ALPHA
				* old_delta_weight;
		neuron.output_weights[this->index].delta_weight = new_delta_weight;
		neuron.output_weights[this->index].weight += new_delta_weight;
	}
}
double Neuron::sum_dow(const Layer &next_layer) const {
	double sum = 0.0;

	// Sum our contributions of the errors at the nodes we feed

	for (int n = 0; n < next_layer.size() - 1; ++n) {
		sum += this->output_weights[n].weight * next_layer[n].gradient;
	}

	return sum;
}

void Neuron::calculate_hidden_gradients(const Layer &next_layer) {
	double dow = sum_dow(next_layer);
	this->gradient = dow * Neuron::activation_derivative(this->output);
}
void Neuron::calculate_output_gradients(double targets) {
	double delta = targets - this->output;
	this->gradient = delta * Neuron::activation_derivative(this->output);
}

double Neuron::activation(double x) {
	// Bring output into [-1..1] range
	return tanh(x);
}

double Neuron::activation_derivative(double x) {
	// Approximation of tanh derivative
	return 1.0 - x * x;
}

void Neuron::feed_forward(const Layer &previous_layer) {
	double sum = 0.0;

	// Sum outputs from the previous layer.
	for (int n = 0; n < previous_layer.size(); ++n)
		sum += previous_layer[n].get_output() * previous_layer[n].output_weights[this->index].weight;

	this->output = Neuron::activation(sum);
}

Neuron::Neuron(int num_outputs, int index) {
	for (int c = 0; c < num_outputs; ++c){
		Connection connection;
		connection.weight = 1.0/2.0;
		this->output_weights.push_back(connection);
	}

	this->index = index;
}

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
	// Update connection weights for all layers except input
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
