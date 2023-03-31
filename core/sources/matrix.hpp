#pragma once

#include <core/assert.hpp>
#include <core/printer.hpp>

template<typename Type>
class Columns{
	Type *m_DataPtr;
	size_t m_M;
public:
	Columns(Type *data_ptr, size_t m):
		m_DataPtr(data_ptr),
		m_M(m)
	{}

	Type &operator[](size_t m){
		SX_ASSERT(m < m_M);
		return m_DataPtr[m];
	}

	size_t M()const {
		return m_M;
	}
};

template<typename Type>
class Matrix: public NonCopyable{
	Type *m_Data = nullptr;
	size_t m_N = 0;
	size_t m_M = 0;
public:
	Matrix(size_t n, size_t m): 
		m_N(n), 
		m_M(m) 
	{ 
		if(!n || !m)
			return;

		m_Data = new Type[m_N * m_M];
	}

	Matrix(Matrix&& other) {
		*this = Move(other);
	}

	~Matrix(){
		Clear();
	}
	Matrix &operator=(Matrix&& other) {
		Clear();
		Swap(m_Data, other.m_Data);
		Swap(m_N, other.m_N);
		Swap(m_M, other.m_M);

		return *this;
	}


	Columns<Type> operator[](size_t n){
		SX_ASSERT(n < m_N);
		return {&m_Data[n * m_M], m_M};
	}

	Columns<const Type> operator[](size_t n)const{
		SX_ASSERT(n < m_N);
		return {&m_Data[n * m_M], m_M};
	}


	size_t N()const{
		return m_N;
	}

	size_t M()const{
		return m_M;
	}

	void Clear() {
		delete[] m_Data;
		m_N = 0;
		m_M = 0;
	}
};

template<typename Type>
struct Printer<Matrix<Type>> {
	static void Print(const Matrix<Type>& matrix, StringWriter& writer) {
		for (int n = 0; n < matrix.N(); n++) {
			Printer<char>::Print('[', writer);
			for (int m = 0; ; m++) {
				Printer<Type>::Print(matrix[n][m], writer);
				if(m == matrix.M() - 1)
					break;
				Printer<char>::Print(',', writer);
			}
			Printer<char>::Print(']', writer);
			Printer<char>::Print('\n', writer);
		}
	}
};
