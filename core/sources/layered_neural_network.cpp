#include <core/assert.hpp>
#include <core/print.hpp>
#include "layered_neural_network.hpp"

LayeredNeuralNetwork::LayeredNeuralNetwork(std::initializer_list<size_t> topology){
	SX_ASSERT(topology.size() > 1);

	auto it = topology.begin();
	size_t input_size = *it++;
	for (; it != topology.end(); ++it){
		m_Layers.Emplace(input_size, *it);
		input_size = *it;
	}
}

List<float> LayeredNeuralNetwork::Do(List<float> input) {
	SX_ASSERT(IsValidInput(input));

	for (Layer& layer : m_Layers)
		input = layer.Process(Move(input));

	return input;
}

