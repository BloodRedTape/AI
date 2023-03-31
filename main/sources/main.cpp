#include "layered_neural_network.hpp"
#include "matrix.hpp"
#include <core/print.hpp>
#include <functional>


int main(){
	LayeredNeuralNetwork net{2, 2, 1};
	net.GetLayer(0).GetNeuron(0).GetWeight(0) = 1.f;
	net.GetLayer(0).GetNeuron(0).GetWeight(1) = 1.f;

	net.GetLayer(0).GetNeuron(1).GetWeight(0) = 1.f;
	net.GetLayer(0).GetNeuron(1).GetWeight(1) = 1.f;

	net.GetLayer(1).GetNeuron(0).GetWeight(0) = -1;
	net.GetLayer(1).GetNeuron(0).GetWeight(1) = 2;

	auto res = net.Do({1.f, 1.f});

	Println("Value: %", res.First());
}