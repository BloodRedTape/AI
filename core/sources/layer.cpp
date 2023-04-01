#include "layer.hpp"

Layer::Layer(size_t input_size, size_t neurons_count) :
	m_InputSize(input_size) {
	for (size_t i = 0; i < neurons_count; i++)
		Emplace(input_size);
}

bool Layer::IsSuitableToBeNext(const Layer& other)const {
	return OutputSize() == other.InputSize();
}

List<float> Layer::Process(ConstSpan<float> inputs) {
	SX_ASSERT(IsValidInput(inputs));

	List<float> output;
	output.Reserve(NeuronsCount());

	for (int neuron = 0; neuron < NeuronsCount(); neuron++)
		output.Add(GetNeuron(neuron).PropagateAndActivate(inputs));

	return output;
}
