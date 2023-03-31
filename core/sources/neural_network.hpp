#pragma once


#include <core/list.hpp>
#include "matrix.hpp"


struct Layer{
	Matrix<float> Weights;

	Layer(size_t input_size, size_t neurons_count);

	bool IsSuitableToBeNext(const Layer &other)const;

	size_t OutputSize()const {
		return Weights.M();
	}

	size_t InputSize()const {
		return Weights.N();
	}

	List<float> Process(List<float> input)const;
};

class NeuralNetwork{
	List<Layer> m_Layers;
public:

	NeuralNetwork(std::initializer_list<size_t> configuration);
	
	List<float> Do(List<float> input);
};