module;
#include <stdexcept>
export module Matrix;
import Vector;

export namespace FloMath {

	template<IntegralType T, size_t Rows, size_t Columns = Rows>
	class Matrix {
	public:
		template<typename ...Args> Matrix(Args ...args) : data{args...} {}

		Vector<T, Rows>& operator[](unsigned index);
		const Vector<T, Rows>& operator[](unsigned index) const;
		Vector<T, Rows>& at(unsigned index);
		const Vector<T, Rows>& at(unsigned index) const;

		//Matrix Addition
		void operator+=(const Matrix<T, Rows, Columns>& other);
		Matrix<T, Rows, Columns> operator+(const Matrix<T, Rows, Columns>& other) const;

		//Scalar Multiplication
		void operator*=(T t);
		Matrix<T, Rows, Columns> operator*(T t) const;

		//Matrix Vector Multiplication
		Vector<T, Columns> operator*(const Vector<T, Columns>& vec) const;

	private:
		Vector<T, Rows> data[Columns];
	};

	//Scalar Multiplication
	template<IntegralType T, size_t Rows, size_t Columns> void operator*=(T t, Matrix<T, Rows, Columns>& mat);
	template<IntegralType T, size_t Rows, size_t Columns> Matrix<T, Rows, Columns> operator*(T t, const Matrix<T, Rows, Columns>& mat);

	//Matrix Multiplication
	template<IntegralType T, size_t Rows, size_t Columns1, size_t Columns2>
	Matrix<T, Rows, Columns2> operator*(const Matrix<T, Rows, Columns1>& mat1, const Matrix<T, Columns1, Columns2>& mat2);

	template<IntegralType T> using Mat2 = Matrix<T, 2>;
	template<IntegralType T> using Mat2x3 = Matrix<T, 2, 3>;
	template<IntegralType T> using Mat2x4 = Matrix<T, 2, 4>;
	template<IntegralType T> using Mat3x2 = Matrix<T, 3, 2>;
	template<IntegralType T> using Mat3 = Matrix<T, 3>;
	template<IntegralType T> using Mat3x4 = Matrix<T, 3, 4>;
	template<IntegralType T> using Mat4x2 = Matrix<T, 4, 2>;
	template<IntegralType T> using Mat4x3 = Matrix<T, 4, 3>;
	template<IntegralType T> using Mat4 = Matrix<T, 4>;

}

module: private;

namespace FloMath {

	template<IntegralType T, size_t Rows, size_t Columns>
	Vector<T, Rows>& Matrix<T, Rows, Columns>::operator[](unsigned index) { return data[index]; }

	template<IntegralType T, size_t Rows, size_t Columns>
	const Vector<T, Rows>& Matrix<T, Rows, Columns>::operator[](unsigned index) const { return data[index]; }

	template<IntegralType T, size_t Rows, size_t Columns>
	Vector<T, Rows>& Matrix<T, Rows, Columns>::at(unsigned index) {
		if(index < Columns) { return data[index]; }
		throw std::runtime_error("Memory Access Violation");
	}

	template<IntegralType T, size_t Rows, size_t Columns>
	const Vector<T, Rows>& Matrix<T, Rows, Columns>::at(unsigned index) const {
		if(index < Columns) { return data[index]; }
		throw std::runtime_error("Memory Access Violation");
	}

	template<IntegralType T, size_t Rows, size_t Columns>
	void Matrix<T, Rows, Columns>::operator+=(const Matrix<T, Rows, Columns>& other) {
		for(int i = 0; i < Columns; ++i) {
			data[i] += other[i];
		}
	}

	template<IntegralType T, size_t Rows, size_t Columns>
	Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator+(const Matrix<T, Rows, Columns>& other) const {
		Matrix<T, Rows, Columns> retval(*this);
		retval += other;
		return retval;
	}

	template<IntegralType T, size_t Rows, size_t Columns>
	void Matrix<T, Rows, Columns>::operator*=(T t) {
		for(int i = 0; i < Columns; ++i) {
			data[i] *= t;
		}
	}

	template<IntegralType T, size_t Rows, size_t Columns>
	Matrix<T, Rows, Columns> Matrix<T, Rows, Columns>::operator*(T t) const {
		Matrix<T, Rows, Columns> retval(*this);
		retval *= t;
		return retval;
	}

	template<IntegralType T, size_t Rows, size_t Columns>
	Vector<T, Columns> Matrix<T, Rows, Columns>::operator*(const Vector<T, Columns>& vec) const {
		Vector<T, Columns> retval;
		for(int i = 0; i < Columns; ++i) {
			retval += vec[i] * data[i];
		}
		return retval;
	}

	//Scalar Multiplication
	template<IntegralType T, size_t Rows, size_t Columns>
	void operator*=(T t, Matrix<T, Rows, Columns>& mat) { mat *= t; }
	template<typename T, size_t Rows, size_t Columns>
	Matrix<T, Rows, Columns> operator*(T t, const Matrix<T, Rows, Columns>& mat) { return mat * t; }

	//Matrix Multiplication
	template<IntegralType T, size_t Rows, size_t Columns1, size_t Columns2>
	Matrix<T, Rows, Columns2> operator*(const Matrix<T, Rows, Columns1>& mat1, const Matrix<T, Columns1, Columns2>& mat2) {
		Matrix<T, Rows, Columns2> retval;
		for(int i = 0; i < Columns1; ++i) {
			for(int j = 0; j < Columns2; ++j) {
				for(int k = 0; k < Rows; ++k) {
					retval[j][k] += mat1[i][k] * mat2[j][i];
				}
			}
		}
		return retval;
	}

}