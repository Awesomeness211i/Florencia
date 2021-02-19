#pragma once
#include "Vector.h"

namespace FloMath {

	template<typename T, unsigned Rows, unsigned Columns>
	class Matrix {
	public:
		template<typename... Args>
		Matrix(Args... args)
			:data{args...}
		{}
		Vector<T, Rows>& operator[](unsigned index) {
			return data[index];
		}
		Vector<T, Rows>& at(unsigned index) {
			if (index < Columns)
				return data[index];
			//throw;
		}
	private:
		Vector<T, Rows> data[Columns];
	};

}
