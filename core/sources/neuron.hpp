#pragma once

#include <core/list.hpp>

using Weight = float;

class Neuron : public List<Weight> {
public:
	Neuron(size_t inputs_size);

	float& GetWeight(size_t index) {
		return At(index);
	}

	const float& GetWeight(size_t index) const {
		return At(index);
	}

	size_t WeightsCount()const {
		return Size();
	}

	float PropagateAndActivate(ConstSpan<float> inputs);
};