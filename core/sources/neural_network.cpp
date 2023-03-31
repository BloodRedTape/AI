#include <core/assert.hpp>
#include "neural_network.hpp"


Layer::Layer(size_t input_size, size_t neurons_count):
	Weights(input_size, neurons_count)
{

}

bool Layer::IsSuitableToBeNext(const Layer& other)const
{
	return OutputSize() == other.InputSize();
}

List<float> Layer::Process(List<float> input)const{
	SX_ASSERT(Weights.N() == input.Size());

	List<float> output;
	output.Reserve(Weights.M());

	for (int i = 0; i < Weights.M(); i++) {
		float result = 0.f;

		for (int j = 0; j < input.Size(); j++) {
			result += input[j] * Weights[j][i];
		}

		output.Add(result);
	}

	return output;
}

NeuralNetwork::NeuralNetwork(std::initializer_list<size_t> configuration){
	SX_ASSERT(configuration.size() > 1);

	auto it = configuration.begin();
	size_t input_size = *it++;
	for (; it != configuration.end(); ++it){
		m_Layers.Add(Layer(input_size, *it));
		input_size = *it;
	}
}

List<float> NeuralNetwork::Do(List<float> input) {

	for (const Layer& layer : m_Layers)
		input = layer.Process(Move(input));

	return input;
}
