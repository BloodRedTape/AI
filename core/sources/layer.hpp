#pragma once

#include "neuron.hpp"

class Layer : public List<Neuron> {
private:
	size_t m_InputSize;
public:
	Layer(size_t input_size, size_t neurons_count);

	Layer(Layer&& other) = default;

	bool IsSuitableToBeNext(const Layer& other)const;

	Neuron& GetNeuron(size_t index) {
		return At(index);
	}

	const Neuron& GetNeuron(size_t index) const {
		return At(index);
	}

	size_t InputSize()const {
		return m_InputSize;
	}

	size_t OutputSize()const {
		return NeuronsCount();
	}

	size_t NeuronsCount()const {
		return Size();
	}

	List<float> Process(List<float> inputs);
};
