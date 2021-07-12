module;
#include <stdexcept>
#include <type_traits>
export module Vector;

namespace FloMath {

	template<typename T>
	concept IntegralType = std::is_integral_v<T> || std::is_floating_point_v<T>;

	export template<IntegralType T, size_t Rows>
	class Vector {
	public:
		template<typename ...Args>
		Vector(Args ...args) : data{args...} {}

		T operator[](unsigned index) { return data[index]; }
		T operator[](unsigned index) const { return data[index]; }
		T at(unsigned index) { if (index < Rows) { return data[index]; } throw std::runtime_error("Memory Access Violation"); }
		T at(unsigned index) const { if (index < Rows) { return data[index]; } throw std::runtime_error("Memory Access Violation"); }

	private:
		T data[Rows] = { 0 };
	};

	/////////////////////////////////////Vector Addition//////////////////////////////////////
	export template<typename T, size_t Rows>
	Vector<T, Rows> operator+(Vector<T, Rows>& vec1, Vector<T, Rows>& vec2) {
		Vector<T, Rows> vec;
		for (int i = 0; i < Rows; i++) {
			vec[i] = vec1[i] + vec2[i];
		}
		return vec;
	}
	export template<typename T, size_t Rows>
	void operator+=(Vector<T, Rows>& vec1, Vector<T, Rows>& vec2) {
		for (int i = 0; i < Rows; i++) {
			vec1[i] += vec2[i];
		}
	}
	//////////////////////////////////Vector Multiplication///////////////////////////////////
	export template<typename T, size_t Rows>
	Vector<T, Rows> operator*(Vector<T, Rows>& vec, T t) {
		Vector<T, Rows> retval;
		for (int i = 0; i < Rows; i++) {
			retval[i] = vec[i] * t;
		}
		return retval;
	}
	export template<typename T, size_t Rows>
	Vector<T, Rows> operator*(T t, Vector<T, Rows>& vec) {
		return vec * t;
	}
	export template<typename T, size_t Rows>
	T operator*(Vector<T, Rows>& vec1, Vector<T, Rows>& vec2) {
		T retval = 0;
		for (int i = 0; i < Rows; i++) {
			retval += vec1[i] * vec2[i];
		}
		return retval;
	}

	export template<typename T> using Vec2 = Vector<T, 2>;
	export template<typename T> using Vec3 = Vector<T, 3>;
	export template<typename T> using Vec4 = Vector<T, 4>;

}