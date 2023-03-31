#pragma once


#include <core/list.hpp>
#include "matrix.hpp"

struct Neuron {
	Span<float> Weights;

	Neuron(Span<float> weights):
		Weights(weights)
	{}

	float &GetWeight(size_t index) {
		return Weights[index];
	}
};

struct Layer{
	Matrix<float> Weights;

	Layer(size_t input_size, size_t neurons_count);

	Layer(Layer &&other) = default;

	bool IsSuitableToBeNext(const Layer &other)const;

	size_t OutputSize()const {
		return Weights.M();
	}

	size_t InputSize()const {
		return Weights.N();
	}

	Neuron GetNeuron(size_t index) {
		return Neuron( { &Weights[index][0], Weights[index].M() });
	}

	List<float> Process(List<float> input)const;

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