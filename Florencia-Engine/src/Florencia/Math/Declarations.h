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
	constexpr double π = 3.14159265358979323846; //ALT-227 for π
	constexpr double e = 2.71828182845904523536;
	constexpr double inf = 1E300 * 1E300; //ALT-236 for ∞
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

	//Operators
	template<typename T, unsigned Dim>
	Vector<T, Dim> operator+(Vector<T, Dim>& vec1, Vector<T, Dim>& vec2) {
		Vector<T, Dim> vec;
		for (int i = 0; i < Dim; i++) {
			vec[i] = vec1[i] + vec2[i];
		}
		return vec;
	}
	template<typename T, unsigned Dim>
	Vector<T, Dim> operator+=(Vector<T, Dim>& vec1, Vector<T, Dim>& vec2) {
		for (int i = 0; i < Dim; i++) {
			vec1[i] = vec1[i] + vec2[i];
		}
		return vec1;
	}

	template<typename T, unsigned Dim>
	Vector<T, Dim> operator*(Vector<T, Dim>& vec, T t) {
		Vector<T, Dim> retval;
		for (int i = 0; i < Dim; i++) {
			retval[i] = vec[i] * t;
		}
		return retval;
	}
	template<typename T, unsigned Dim>
	Vector<T, Dim> operator*(T t, Vector<T, Dim>& vec) {
		return vec * t;
	}
	template<typename T, unsigned Dim1, unsigned Dim2>
	Vector<T, Dim1> operator*(Matrix<T, Dim1, Dim2>& mat, Vector<T, Dim1>& vec) {
		Vector<T, Dim1> retval;
		for (int i = 0; i < Dim1; i++) {
			retval += vec[i] * mat[i];
		}
	}
	template<typename T, unsigned Dim>
	T operator*(Vector<T, Dim>& vec1, Vector<T, Dim>& vec2) {
		T retval = (T)0;
		for (int i = 0; i < Dim; i++) {
			retval += vec1[i] * vec2[i];
		}
		return retval;
	}

	template<typename T, unsigned Dim1, unsigned Dim2>
	Matrix<T, Dim1, Dim2> operator*(Matrix<T, Dim1, Dim2>& mat, T t) {
		Matrix<T, Dim1, Dim2> retval;
		for (int i = 0; i < Dim2; i++) {
			retval[i] = mat[i] * t;
		}
		return retval;
	}
	template<typename T, unsigned Dim1, unsigned Dim2>
	Matrix<T, Dim1, Dim2> operator*(T t, Matrix<T, Dim1, Dim2>& mat) {
		return mat * t;
	}
	template<typename T, unsigned Dim1, unsigned Dim2>
	Matrix<T, Dim1, Dim2> operator*=(Matrix<T, Dim1, Dim2>& mat, T t) {
		mat = mat * t;
		return mat;
	}
	template<typename T, unsigned Dim1, unsigned Dim2, unsigned Dim3>
	Matrix<T, Dim1, Dim3> operator*(Matrix<T, Dim1, Dim2>& mat1, Matrix<T, Dim2, Dim3>& mat2) {
		Matrix<T, Dim1, Dim3> retval;
		for (int i = 0; i < Dim2; i++) {
			for (int j = 0; j < Dim3; j++) {
				Vector<T, Dim1> vec = mat1[i] * mat2[j][i];
				retval[j] += vec;
			}
		}
		return retval;
	}

}