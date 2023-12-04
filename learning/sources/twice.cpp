#include <core/print.hpp>
#include <core/list.hpp>
#include <core/pair.hpp>
#include <core/array.hpp>
#include <functional>

struct Model {
	static constexpr Pair<float, float> s_TrainData[] = {
		{1, 1},
		{2, 4},
		{3, 6},
		{4, 8},
	};

	float W = (rand() / RAND_MAX) * 20.f;

	float MSECost()const {
		float sum = 0.f;

		for (const auto &[input, expected_output]: s_TrainData) {
			float output = Do(input);
			float difference = output - expected_output;
			sum += difference * difference;
		}

		return sum / std::size(s_TrainData);
	}

	float Do(float input)const{
		return W * input;
	}

	void Train(float learning_rate = 0.01) {
		float eps = 0.0001;
		float dt = (Model({ W + eps }).MSECost() - MSECost())/eps;
		W -= dt * learning_rate;
	}

	void TrainIterative(float rate, int times) {
		for (int i = 0; i < times; i++) {
			Train(rate);
		}
	}
};

float TrainModel(float rate, int epoch) {
	Model m;
	Println("Ini Cost: %", m.MSECost());
	m.TrainIterative(rate, epoch);
	Println("Final Cost: %", m.MSECost());
	return m.MSECost();
}

int main(){
	TrainModel(0.02, 400);
}