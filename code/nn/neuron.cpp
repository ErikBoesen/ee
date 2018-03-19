#include <vector>
#include <cmath>
#include "neuron.h"

#define ETA 0.05 // Learning rate [0..1]
#define ALPHA 0.5 // Momentum (multiplier of last change in weight) [0..]

using namespace std;


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
