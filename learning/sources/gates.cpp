#include <core/print.hpp>
#include <core/pair.hpp>
#include <core/os/clock.hpp>
#include <random>

float Sigmoid(float x) {
	return 1.f / (1.f + expf(-x));
}

float RandFloat(float min, float max) {
	float length = max - min;
	return min + (float(rand()) / RAND_MAX) * length;
}

struct Model {
	static constexpr float s_TrainData[][3] = {
		{0, 0, 0},
		{1, 0, 1},
		{0, 1, 1},
		{1, 1, 1},
	};

	static constexpr float Eps = 0.0001;

	static constexpr float InitialRange = 1.f;

	float W1 = RandFloat(-1, 1) * InitialRange;
	float W2 = RandFloat(-1, 1) * InitialRange;
	float B  = RandFloat(-1, 1) * InitialRange;

	float MSECost()const {
		float sum = 0.f;

		for (const auto &[x1, x2, y]: s_TrainData) {
			float output = Do(x1, x2);
			float difference = output - y;
			sum += difference * difference;
		}

		return sum / std::size(s_TrainData);
	}

	float Do(float x1, float x2)const{
		return Sigmoid(W1 * x1 + W2 * x2 - B);
	}

	void Train(float learning_rate = 0.01) {
		float d1 = (Model({ W1 + Eps , W2		, B      }).MSECost() - MSECost())/Eps;
		float d2 = (Model({ W1,		   W2 + Eps , B      }).MSECost() - MSECost())/Eps;
		float db = (Model({ W1,		   W2       , B + Eps}).MSECost() - MSECost())/Eps;

		W1 -= d1 * learning_rate;
		W2 -= d2 * learning_rate;
		B  -= db * learning_rate;
	}

	void TrainIterative(float rate, int times) {
		for (int i = 0; i < times; i++) {
			Train(rate);
		}
	}

	void TrainModel(float rate, int epoch) {
		Println("Ini Cost: %", MSECost());
		TrainIterative(rate, epoch);
		Println("Final Cost: %", MSECost());
	}

	void PrintAccurancy() {
		for (const auto& [x1, x2, y] : s_TrainData) {
			float o = Do(x1, x2);

			Println("X1=%, X2=%, Y = %, TY = %", x1, x2, o, y);
		}
	}
};

int main() {
	Println("Gates");
	//srand(Clock::GetMonotonicTime().AsMicroseconds());
	srand(69);
	Model m;
	m.TrainModel(0.01, 100000);
	m.PrintAccurancy();
}
