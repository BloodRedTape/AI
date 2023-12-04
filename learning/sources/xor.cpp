#include <core/print.hpp>
#include <core/pair.hpp>
#include <core/os/clock.hpp>
#include <core/array.hpp>
#include <core/ranges.hpp>
#include <random>

#define PRINT_DELTA 0
#define PRINT_COST 1


float Sigmoid(float x) {
	return 1.f / (1.f + expf(-x));
}

float RandFloat(float min, float max) {
	float length = max - min;
	return min + (float(rand()) / RAND_MAX) * length;
}

struct Xor {
	static constexpr float s_TrainData[][3] = {
		{0, 0, 0},
		{1, 0, 1},
		{0, 1, 1},
		{1, 1, 0},
	};

	static constexpr float InitialRange = 1.f;
	static constexpr float Eps = 0.0001;

	
	Array<float, 9> Parameters = {};

	Xor() {
		for(float &p: Parameters)
			p = RandFloat(-1, 1) * InitialRange;
	}

	Xor(const Xor& xor, size_t index, float value) {
		Parameters = xor.Parameters;
		Parameters[index] = value;
	}

	float MSECost()const {
		float sum = 0.f;

		for (const auto& [x1, x2, y] : s_TrainData) {
			float output = Do(x1, x2);
			float difference = output - y;
			sum += difference * difference;
		}

		return sum / std::size(s_TrainData);
	}

	float Do(float x1, float x2)const {
		float or = Sigmoid(Parameters[0] * x1 + Parameters[1] * x2 - Parameters[2]);
		float nand = Sigmoid(Parameters[3] * x1 + Parameters[4] * x2 - Parameters[5]);
		float and = Sigmoid(Parameters[6] * or + Parameters[7] * nand - Parameters[8]);
		return and;
	}


	void Train(float learning_rate = 0.01) {
		for (const auto &[parameter, index] : IndexedRange(Parameters)) {
			float delta = (Xor(*this, index, parameter + Eps).MSECost() - MSECost())/Eps;

#if PRINT_DELTA
			Println("Delta: %", delta);
#endif 

			Parameters[index] -= delta;
		}
	}

	void TrainIterative(float rate, int times) {
		for (int i = 0; i < times; i++) {
			Train(rate);
		}
	}

	void TrainModel(float rate, int epoch) {
#if PRINT_COST
		Println("Ini Cost: %", MSECost());
#endif
		TrainIterative(rate, epoch);
#if PRINT_COST
		Println("Final Cost: %", MSECost());
#endif
	}

	void PrintAccurancy() {
		for (const auto& [x1, x2, y] : s_TrainData) {
			float o = Do(x1, x2);

			Println("X1=%, X2=%, Y = %, TY = %", x1, x2, o, y);
		}
	}
};

int main() {
	srand(99);
	Xor m;
	Println("Xor");
	Println("%", m.Parameters);
	//srand(Clock::GetMonotonicTime().AsMicroseconds());
	//m.Train(0.001);
	m.TrainModel(0.01, 100000);
	Println("%", m.Parameters);
	m.PrintAccurancy();
}
