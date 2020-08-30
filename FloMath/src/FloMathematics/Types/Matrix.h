#pragma once
#include "Vector.h"

namespace FloMath {

	template<typename T, unsigned Dim1, unsigned Dim2>
	class Matrix {
	public:

	private:
		Vector<T, Dim1> data[Dim2];
	};

}