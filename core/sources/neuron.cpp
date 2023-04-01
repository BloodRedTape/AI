#include "neuron.hpp"

Neuron::Neuron(size_t inputs_size) {
	Reserve(inputs_size);

	auto fill_function = [](){
		return 0.f; 
	};

	for (size_t i = 0; i < inputs_size; i++)
		Add(fill_function());
}

float Neuron::PropagateAndActivate(ConstSpan<float> inputs) {
	SX_ASSERT(IsValidInput(inputs));

	float propagation_result = 0.f;

	for (size_t i = 0; i < inputs.Size(); i++) {
		propagation_result += inputs[i] * GetWeight(i);
	}

	float activation_result = 1.f * propagation_result;

	return activation_result;
}
