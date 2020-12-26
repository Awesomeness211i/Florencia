#pragma once
#include <stdint.h>

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using Uint8 = uint8_t;
using Uint16 = uint16_t;
using Uint32 = uint32_t;
using Uint64 = uint64_t;

namespace FloMath {

	//Constants
	constexpr double π = 3.14159265358979323846; //To get this symbol do ALT-227
	constexpr double e = 2.71828182845904523536;
	constexpr double inf = 1E300 * 1E300; //To get this symbol do ALT-236
	constexpr double NaN = inf * 0.0; //Not A Number
	constexpr double pi = π;

	//Classes
	template<typename T, unsigned Dim>
	class Vector;

	template<typename T, unsigned Dim1, unsigned Dim2 = Dim1>
	class Matrix;

	//Types
	template<typename T>
	using Vec2 = Vector<T, 2>;
	template<typename T>
	using Vec3 = Vector<T, 3>;
	template<typename T>
	using Vec4 = Vector<T, 4>;

	template<typename T>
	using Mat2 = Matrix<T, 2>;
	template<typename T>
	using Mat2x3 = Matrix<T, 2, 3>;
	template<typename T>
	using Mat2x4 = Matrix<T, 2, 4>;
	template<typename T>
	using Mat3x2 = Matrix<T, 3, 2>;
	template<typename T>
	using Mat3 = Matrix<T, 3>;
	template<typename T>
	using Mat3x4 = Matrix<T, 3, 4>;
	template<typename T>
	using Mat4x2 = Matrix<T, 4, 2>;
	template<typename T>
	using Mat4x3 = Matrix<T, 4, 3>;
	template<typename T>
	using Mat4 = Matrix<T, 4>;

	/*template<typename T, unsigned Dim>
	Vector<T, Dim> operator+(Vector<T, Dim>& vec1, Vector<T, Dim>& vec2) {
		
	}*/

	template<typename T, unsigned Dim1, unsigned Dim2, unsigned Dim3>
	Matrix<T, Dim1, Dim3> operator*(Matrix<T, Dim1, Dim2>& mat1, Matrix<T, Dim2, Dim3>& mat2) {
		Matrix<T, Dim1, Dim3> mat;
		for (int i = 0; i < Dim1; i++) {
			for (int j = 0; j < Dim3; j++) {
				mat[i][j] = i + j;
			}
		}
		return mat;
	}

}