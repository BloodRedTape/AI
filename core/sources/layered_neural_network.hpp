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

	size_t InputSize()const {
		return m_Layers.First().NeuronsCount();
	}

	size_t OutputSize()const {
		return m_Layers.Last().NeuronsCount();
	}

	bool IsValidInput(ConstSpan<float> inputs)const {
		return inputs.Size() == InputSize();
	}
};