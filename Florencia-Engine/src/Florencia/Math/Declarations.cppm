export module Declarations;
import Vector;
import Matrix;

export namespace FloMath {

	//Constants
	constexpr double π = 3.141592653589793; //ALT-227 for symbol
	constexpr double pi = 3.14159265358979323846;
	constexpr double e = 2.71828182845904523536;
	constexpr double inf = 1E154 * 1E154; //ALT-236 for ∞
	constexpr double NaN = inf * 0.0; //Not A Number

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

	//////////////////////////////////////Vector Addition/////////////////////////////////////
	template<typename T, size_t Rows>
	Vector<T, Rows> operator+(Vector<T, Rows>& vec1, Vector<T, Rows>& vec2) {
		Vector<T, Rows> vec;
		for (int i = 0; i < Rows; i++) {
			vec[i] = vec1[i] + vec2[i];
		}
		return vec;
	}
	template<typename T, size_t Rows>
	void operator+=(Vector<T, Rows>& vec1, Vector<T, Rows>& vec2) {
		for (int i = 0; i < Rows; i++) {
			vec1[i] = vec1[i] + vec2[i];
		}
	}
	//////////////////////////////////Vector Multiplication///////////////////////////////////
	template<typename T, size_t Rows>
	Vector<T, Rows> operator*(Vector<T, Rows>& vec, T t) {
		Vector<T, Rows> retval;
		for (int i = 0; i < Rows; i++) {
			retval[i] = vec[i] * t;
		}
		return retval;
	}
	template<typename T, size_t Rows>
	Vector<T, Rows> operator*(T t, Vector<T, Rows>& vec) {
		return vec * t;
	}
	template<typename T, size_t Rows>
	T operator*(Vector<T, Rows>& vec1, Vector<T, Rows>& vec2) {
		T retval = 0;
		for (int i = 0; i < Rows; i++) {
			retval += vec1[i] * vec2[i];
		}
		return retval;
	}
	////////////////////////////////////Matrix Addition///////////////////////////////////////
	template<typename T, size_t Rows, size_t Columns>
	Matrix<T, Rows, Columns> operator+(Matrix<T, Rows, Columns>& mat, Matrix<T, Rows, Columns>& mat2) {
		Matrix<T, Rows, Columns> retval;
		for (int i = 0; i < Columns; i++) {
			retval[i] += mat[i] + mat2[i];
		}
		return retval;
	}
	/////////////////////////////////Matrix Multiplication////////////////////////////////////
	template<typename T, size_t Rows, size_t Columns>
	Vector<T, Columns> operator*(Matrix<T, Rows, Columns>& mat, Vector<T, Columns>& vec) {
		Vector<T, Columns> retval;
		for (int i = 0; i < Columns; i++) {
			Vector<T, Columns> temp = vec[i] * mat[i];
			retval += temp;
		}
		return retval;
	}
	template<typename T, size_t Rows, size_t Columns>
	Matrix<T, Rows, Columns> operator*(Matrix<T, Rows, Columns>& mat, T t) {
		Matrix<T, Rows, Columns> retval;
		for (int i = 0; i < Columns; i++) {
			retval[i] = mat[i] * t;
		}
		return retval;
	}
	template<typename T, size_t Rows, size_t Columns1, size_t Columns2>
	Matrix<T, Rows, Columns2> operator*(Matrix<T, Rows, Columns1>& mat1, Matrix<T, Columns1, Columns2>& mat2) {
		Matrix<T, Rows, Columns2> retval;
		for (int i = 0; i < Columns1; i++) {
			for (int j = 0; j < Columns2; j++) {
				Vector<T, Rows> vec = mat1[i] * mat2[j][i];
				retval[j] += vec;
			}
		}
		return retval;
	}
	template<typename T, size_t Rows, size_t Columns>
	Matrix<T, Rows, Columns> operator*(T t, Matrix<T, Rows, Columns>& mat) {
		return mat * t;
	}
	template<typename T, size_t Rows, size_t Columns>
	void operator*=(Matrix<T, Rows, Columns>& mat, T t) {
		mat = mat * t;
	}
	template<typename T, size_t Rows>
	void operator*=(Matrix<T, Rows>& mat1, Matrix<T, Rows>& mat2) {
		mat1 = mat1 * mat2;
	}
}