package nn

import (
    "math/rand"
    "math"
)

const (
    ETA float64 = 0.15 // training rate
    ALPHA float64 = 0.5 // training momentum
)

type Connection struct {
    weight float64
    delta_weight float64
}

type Neuron struct {
    output float64
    output_weights []Connection
    index int
    gradient float64
}

type Layer []Neuron

func (n Neuron) UpdateInputWeights(previous_layer *Layer) {
    for _, neuron := range *previous_layer {
        old_delta_weight := neuron.output_weights[n.index].delta_weight

        new_delta_weight :=
            // Individual input, magnified by gradient and train rate
            ETA * neuron.output * n.gradient +
            // Also add momentum (fraction of previous delta weight)
            ALPHA * old_delta_weight

        neuron.output_weights[n.index].delta_weight = new_delta_weight
        neuron.output_weights[n.index].weight += new_delta_weight
    }
}

func (n Neuron) SumDOW(next_layer *Layer) float64 {
    sum := 0.0
    for i := 0; i < len(*next_layer) - 1; i++ {
        sum += n.output_weights[i].weight * (*next_layer)[i].gradient
    }
    return sum
}

func (n Neuron) CalculateHiddenGradients(next_layer *Layer) {
    dow := n.SumDOW(next_layer)
    n.gradient = dow * n.ActivationDerivative(n.output)
}
func (n Neuron) CalculateOutputGradients(target float64) {
    delta := target - n.output
    n.gradient = delta * n.ActivationDerivative(n.output)
}

func (n Neuron) Activation(x float64) float64 {
    return math.Tanh(x);
}
func (n Neuron) ActivationDerivative(x float64) float64 {
    // Approximation of derivative of tanh
    return 1.0 - x*x
}

// TODO: Not an apt name
func (n Neuron) FeedForward(previous_layer *Layer) {
    sum := 0.0

    // Sum outputs from the previous layer.
    for _, neuron := range *previous_layer {
        // TODO: there may be duplication issues here
        sum += neuron.output * neuron.output_weights[n.index].weight
    }

    n.output = n.Activation(sum)
}

func (n Neuron) New(num_outputs int, index int) {
    for c := 0; c < num_outputs; c++ {
        n.output_weights = append(n.output_weights, Connection{weight: rand.Float64()})
    }
    n.index = index
}
