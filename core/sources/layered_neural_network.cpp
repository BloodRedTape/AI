#include <core/assert.hpp>
#include <core/print.hpp>
#include "layered_neural_network.hpp"

LayeredNeuralNetwork::LayeredNeuralNetwork(std::initializer_list<size_t> configuration){
	SX_ASSERT(configuration.size() > 1);

	auto it = configuration.begin();
	size_t input_size = *it++;
	for (; it != configuration.end(); ++it){
		m_Layers.Emplace(input_size, *it);
		input_size = *it;
	}
}

List<float> LayeredNeuralNetwork::Do(List<float> input) {
	for (Layer& layer : m_Layers)
		input = layer.Process(Move(input));

	return input;
}

