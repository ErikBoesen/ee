#pragma once
#include <vector>
#include "connection.h"

using namespace std;

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
