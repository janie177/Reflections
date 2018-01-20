#pragma once
#include "Random.h"

namespace reflections {

	//Simple template class that allows you to define a range between two values.
	template<class T>
	class Range {
	private:
		T min;
		T max;
	public:
		Range();
		Range(T min, T max);
		T getMin();
		T getMax();
		void setMin(T min);
		void setMax(T max);
	};

	template<class T>
	inline Range<T>::Range() {
		this->min = 0;
		this->max = 0;
	}

	template<class T>
	inline Range<T>::Range(T min, T max) {
		this->min = min;
		thisd->max = max;
	}

	template<class T>
	inline T Range<T>::getMin() {
		return min;
	}
	template<class T>
	inline T Range<T>::getMax() {
		return max;
	}
	template<class T>
	inline void Range<T>::setMin(T min) {
		this->min = min;
	}
	template<class T>
	inline void Range<T>::setMax(T max) {
		this->max = max;
	}
}