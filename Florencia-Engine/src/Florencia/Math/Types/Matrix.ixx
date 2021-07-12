module;
#include <stdexcept>
#include <type_traits>
export module Matrix;
import Vector;

namespace FloMath {

	template<typename T>
	concept IntegralType = std::is_integral_v<T> || std::is_floating_point_v<T>;

	export template<typename T, size_t Rows, size_t Columns = Rows>
	class Matrix {
	public:
		template<typename ...Args>
		Matrix(Args ...args) : data{args...} {}

		Vector<T, Rows> operator[](unsigned index) {
			return data[index];
		}

		Vector<T, Rows> at(unsigned index) {
			if (index < Columns)
				return data[index];
			throw std::runtime_error("Memory Access Violation");
		}

		Vector<T, Rows> operator[](unsigned index) const {
			return data[index];
		}

		Vector<T, Rows> at(unsigned index) const {
			if (index < Columns)
				return data[index];
			throw std::runtime_error("Memory Access Violation");
		}

	private:
		Vector<T, Rows> data[Columns];
	};

	////////////////////////////////////Matrix Addition///////////////////////////////////////
	export template<typename T, size_t Rows, size_t Columns>
	Matrix<T, Rows, Columns> operator+(Matrix<T, Rows, Columns>& mat, Matrix<T, Rows, Columns>& mat2) {
		Matrix<T, Rows, Columns> retval;
		for (int i = 0; i < Columns; i++) {
			retval[i] += mat[i] + mat2[i];
		}
		return retval;
	}
	/////////////////////////////////Matrix Multiplication////////////////////////////////////
	export template<typename T, size_t Rows, size_t Columns>
	Vector<T, Columns> operator*(Matrix<T, Rows, Columns>& mat, Vector<T, Columns>& vec) {
		Vector<T, Columns> retval;
		for (int i = 0; i < Columns; i++) {
			Vector<T, Columns> temp = vec[i] * mat[i];
			retval += temp;
		}
		return retval;
	}
	export template<typename T, size_t Rows, size_t Columns>
	Matrix<T, Rows, Columns> operator*(Matrix<T, Rows, Columns>& mat, T t) {
		Matrix<T, Rows, Columns> retval;
		for (int i = 0; i < Columns; i++) {
			retval[i] = mat[i] * t;
		}
		return retval;
	}
	export template<typename T, size_t Rows, size_t Columns1, size_t Columns2>
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
	export template<typename T, size_t Rows, size_t Columns>
	Matrix<T, Rows, Columns> operator*(T t, Matrix<T, Rows, Columns>& mat) {
		return mat * t;
	}
	export template<typename T, size_t Rows, size_t Columns>
	void operator*=(Matrix<T, Rows, Columns>& mat, T t) {
		mat = mat * t;
	}
	export template<typename T, size_t Rows>
	void operator*=(Matrix<T, Rows>& mat1, Matrix<T, Rows>& mat2) {
		mat1 = mat1 * mat2;
	}

	export template<typename T> using Mat2 = Matrix<T, 2>;
	export template<typename T> using Mat2x3 = Matrix<T, 2, 3>;
	export template<typename T> using Mat2x4 = Matrix<T, 2, 4>;
	export template<typename T> using Mat3x2 = Matrix<T, 3, 2>;
	export template<typename T> using Mat3 = Matrix<T, 3>;
	export template<typename T> using Mat3x4 = Matrix<T, 3, 4>;
	export template<typename T> using Mat4x2 = Matrix<T, 4, 2>;
	export template<typename T> using Mat4x3 = Matrix<T, 4, 3>;
	export template<typename T> using Mat4 = Matrix<T, 4>;

}