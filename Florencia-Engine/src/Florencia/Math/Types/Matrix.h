#pragma once
#include <Math/Types/Vector.h>

namespace FloMath {

	template<typename T, unsigned Dim1, unsigned Dim2>
	class Matrix {
	public:
		template<typename... Args>
		Matrix(Args... args)
			:data{args...}
		{}
		Vector<T, Dim1>& operator[](unsigned index) {
			return data[index];
		}
		Vector<T, Dim1>& at(unsigned index) {
			if (index < Dim1)
				return data[index];
			//throw;
		}
	private:
		Vector<T, Dim1> data[Dim2];
	};

}