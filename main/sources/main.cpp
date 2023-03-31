#include "neural_network.hpp"
#include "matrix.hpp"
#include <core/print.hpp>
#include <functional>

struct NumberIterator {
	int Current;
	int Step;

	NumberIterator(int current, int step) :
		Current(current),
		Step(step) {}

	int operator*()const {
		return Current;
	}

	NumberIterator& operator++() {
		Current += Step;
		return *this;
	}

	bool operator !=(const NumberIterator& it)const {
		return it.Current != Current;
	}
};

auto IntRange(int Begin, int End, int Step = 1) {
	return Range<NumberIterator>{
		{ Begin, Step },
		{ End, Step }
	};
}


#include <string>
#include <core/print.hpp>
#include <core/ranges/filtered.hpp>
#include <core/ranges/transformed.hpp>
#include <core/ranges/algorithm.hpp>


struct Condition{
	int Divisor;
	std::string String;
};

bool IsDivisible(Condition condition, int number) {
	return number % condition.Divisor == 0;
};

auto SelectDivisibleBy(Span<Condition> conditions) {
	return Filtered([=](auto num) {
		auto divisible = std::bind(IsDivisible, std::placeholders::_1, num);

		return conditions | ContainsByPredicate(filter);
	});
}

auto MapToString(Span<Condition> conditions) {
	return Transformed([=](auto num) {
		std::string Result;

		auto divisible = std::bind(IsDivisible, std::placeholders::_1, num);

		for (auto condition : conditions | Filtered(divisible) )
			Result += condition.String;

		return Result;
	});
}


template<typename...ArgsType>
void LetsTakeMillionArgs(ArgsType...args) {

}

int main(){
	LetsTakeMillionArgs(1);
	LetsTakeMillionArgs("Hey", 1);
	LetsTakeMillionArgs("hello", 3.f, 1, Condition());


	List<Condition> conditions;
	conditions.Emplace(3, "Fizz");
	conditions.Emplace(5, "Buzz");

	for (std::string string : IntRange(1, 100) | SelectDivisibleBy(conditions) | MapToString(conditions))
		Println("%", string.c_str());

}