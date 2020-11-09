#pragma once
#include "Vector.h"

namespace FloMath {

	template<typename T, unsigned Dim1, unsigned Dim2>
	class Matrix {
	public:

	private:
		Vector<T, Dim1> data[Dim2];
	};

	typedef Matrix<int, 2, 2> Mat2i;
	typedef Matrix<int, 3, 3> Mat3i;
	typedef Matrix<int, 4, 4> Mat4i;
	typedef Matrix<unsigned, 2, 2> Mat2Ui;
	typedef Matrix<unsigned, 3, 3> Mat3Ui;
	typedef Matrix<unsigned, 4, 4> Mat4Ui;
	typedef Matrix<float, 2, 2> Mat2f;
	typedef Matrix<float, 3, 3> Mat3f;
	typedef Matrix<float, 4, 4> Mat4f;

}