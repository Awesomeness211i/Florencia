#pragma once
#include <stdexcept>


namespace FloMath {
	template<typename T> concept IntegralType = std::integral<T> || std::floating_point<T>;

	template<IntegralType T, size_t Rows>
	class Vector {
	public:
		template<typename ...Args>
		Vector(Args ...args) : data{(T)args...} {}

		T& operator[](unsigned index) { return data[index]; }
		const T& operator[](unsigned index) const { return data[index]; }

		T& at(unsigned index) { if (index < Rows) { return data[index]; } throw std::runtime_error("Memory Access Violation"); }
		const T& at(unsigned index) const { if (index < Rows) { return data[index]; } throw std::runtime_error("Memory Access Violation"); }

		//Vector Addition
		void operator+=(const Vector<T, Rows>& other) { for (int i = 0; i < Rows; ++i) { data[i] += other[i]; } }
		void operator-=(const Vector<T, Rows>& other) { data += (other * -1); }

		Vector<T, Rows> operator+(const Vector<T, Rows>& other) const { Vector<T, Rows> retval(*this); retval += other; return retval; }
		Vector<T, Rows> operator-(const Vector<T, Rows>& other) const { return (*this) + (other * -1); }
		
		//Adding Scalars
		Vector<T, Rows> operator+(T value) const { Vector<T, Rows> retval(*this); for (int i = 0; i < Rows; i++) { retval[i] += value; } return retval; }
		Vector<T, Rows> operator-(T value) const { return (*this) + (-value); }

		//Scalar multiplication
		void operator*=(T t) { for (int i = 0; i < Rows; ++i) { data[i] *= t; } }
		Vector<T, Rows> operator*(T t) const { Vector<T, Rows> retval(*this); retval *= t; return retval; }
		Vector<T, Rows> operator/(T t) const { if (t != 0) { return (*this) * (1 / t); } throw std::runtime_error("Can't divide by 0"); }

		//Vector Dot Product
		//T operator*(const Vector<T, Rows>& other) const { T retval = 0; for (int i = 0; i < Rows; ++i) { retval += data[i] * other[i]; } return retval; }

	private:
		T data[Rows];
	};

	//Scalar Multiplication
	template<typename T, size_t Rows> Vector<T, Rows> operator*(T t, const Vector<T, Rows>& vec) { return vec * t; }

	template<typename T> using Vec2 = Vector<T, 2>;
	template<typename T> using Vec3 = Vector<T, 3>;
	template<typename T> using Vec4 = Vector<T, 4>;
}