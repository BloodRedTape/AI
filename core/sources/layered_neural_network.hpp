#pragma once

#include "layer.hpp"

class LayeredNeuralNetwork{
private:
	List<Layer> m_Layers;
public:
	LayeredNeuralNetwork(std::initializer_list<size_t> topology);
	
	List<float> Do(List<float> inputs);

	Layer &GetLayer(size_t index){
		return m_Layers[index];
	}
};