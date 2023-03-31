#pragma once


#include <core/list.hpp>
#include <core/function.hpp>
#include "matrix.hpp"

struct Neuron {
	Span<float> Weights;

	Neuron(Span<float> weights):
		Weights(weights)
	{}

	float &GetWeight(size_t index) {
		return Weights[index];
	}

	size_t WeightsCount()const {
		return Weights.Size();
	}
};

struct Layer{
	Matrix<float> Weights;
	Function<float(ConstSpan<float>, ConstSpan<float>)> PropagationFunction = &Layer::WeightedSum;

	Layer(size_t input_size, size_t neurons_count);

	Layer(Layer &&other) = default;

	bool IsSuitableToBeNext(const Layer &other)const;

	size_t OutputSize()const {
		return Weights.N();
	}

	size_t InputSize()const {
		return Weights.M();
	}

	Neuron GetNeuron(size_t index) {
		return Neuron( { &Weights[index][0], Weights[index].M() });
	}

	size_t NeuronsCount()const {
		return OutputSize();
	}

	List<float> Process(List<float> input);

	static float WeightedSum(ConstSpan<float> inputs, ConstSpan<float> weights);
};

class NeuralNetwork{
	List<Layer> m_Layers;
public:

	NeuralNetwork(std::initializer_list<size_t> configuration);
	
	List<float> Do(List<float> input);

	void Print();

	Layer &GetLayer(size_t index){
		return m_Layers[index];
	}
};