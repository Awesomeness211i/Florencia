#pragma once
#include <Math/Declarations.h>

namespace FloMath {

	template<typename T, unsigned Dim1, unsigned Dim2>
	class Matrix {
	public:
		Vector<T, Dim1>& operator[](int index) {
			if (index < Dim1) {
				return data[index];
			}
			//return (Vector<T, Dim1>)0;
		}
	private:
		Vector<T, Dim1> data[Dim2];
	};

}