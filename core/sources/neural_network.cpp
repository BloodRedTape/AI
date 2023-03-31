#include <core/assert.hpp>
#include <core/print.hpp>
#include "neural_network.hpp"


Layer::Layer(size_t input_size, size_t neurons_count):
	Weights(neurons_count, input_size)
{

}

bool Layer::IsSuitableToBeNext(const Layer& other)const
{
	return OutputSize() == other.InputSize();
}

List<float> Layer::Process(List<float> input){
	SX_ASSERT(Weights.M() == input.Size());

	List<float> output;
	output.Reserve(Weights.N());

	for (int neuron = 0; neuron < NeuronsCount(); neuron++) {
		float result = PropagationFunction(input, GetNeuron(neuron).Weights);
		output.Add(result);
	}

	return output;
}

float Layer::WeightedSum(ConstSpan<float> inputs, ConstSpan<float> weights) {
	float result = 0.f;

	for (int j = 0; j < inputs.Size(); j++) {
		result += inputs[j] * weights[j];
	}

	return result;
}

NeuralNetwork::NeuralNetwork(std::initializer_list<size_t> configuration){
	SX_ASSERT(configuration.size() > 1);

	auto it = configuration.begin();
	size_t input_size = *it++;
	for (; it != configuration.end(); ++it){
		m_Layers.Emplace(input_size, *it);
		input_size = *it;
	}
}

List<float> NeuralNetwork::Do(List<float> input) {
	for (Layer& layer : m_Layers){
		input = layer.Process(Move(input));
	}

	return input;
}

void NeuralNetwork::Print() {
	for (const Layer& layer : m_Layers) {
		Println("%\n", layer.Weights);
	}
}
