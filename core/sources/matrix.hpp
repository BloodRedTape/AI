#pragma once

#include <core/assert.hpp>

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
};

template<typename Type>
class Matrix{
	Type *m_Data = nullptr;
	size_t m_N;
	size_t m_M;
public:
	Matrix(size_t n, size_t m): 
		m_N(n), 
		m_M(m) 
	{ 
		if(!n || !m)
			return;

		m_Data = new Type[m_N * m_M];
	}

	~Matrix(){
		delete[] m_Data;
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
};
