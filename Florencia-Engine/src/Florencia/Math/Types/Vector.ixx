export module Vector;
import <concepts>;

template<typename T> concept IntegralType = std::integral<T> || std::floating_point<T>;

export namespace FloMath {

	template<IntegralType T, size_t Rows>
	class Vector {
	public:
		template<typename ...Args>
		Vector(Args ...args) : data{args...} {}

		T& operator[](unsigned index);
		const T& operator[](unsigned index) const;
		T& at(unsigned index);
		const T& at(unsigned index) const;

		//Vector Addition
		void operator+=(const Vector<T, Rows>& other);
		Vector<T, Rows> operator+(const Vector<T, Rows>& other) const;

		//Scalar multiplication
		void operator*=(T t);
		Vector<T, Rows> operator*(T t) const;

		//Vector Dot Product
		T operator*(const Vector<T, Rows>& other) const;

	private:
		T data[Rows];
	};

	//Scalar Multiplication
	template<typename T, size_t Rows> Vector<T, Rows> operator*(T t, const Vector<T, Rows>& vec) { return vec * t; }

	template<typename T> using Vec2 = Vector<T, 2>;
	template<typename T> using Vec3 = Vector<T, 3>;
	template<typename T> using Vec4 = Vector<T, 4>;

}

module: private;
import <stdexcept>;


namespace FloMath {

	template<IntegralType T, size_t Rows> T& Vector<T, Rows>::operator[](unsigned index) { return data[index]; }
	template<IntegralType T, size_t Rows> const T& Vector<T, Rows>::operator[](unsigned index) const { return data[index]; }

	template<IntegralType T, size_t Rows> T& Vector<T, Rows>::at(unsigned index) {
		if(index < Rows) { return data[index]; }
		throw std::runtime_error("Memory Access Violation");
	}

	template<IntegralType T, size_t Rows> const T& Vector<T, Rows>::at(unsigned index) const {
		if(index < Rows) { return data[index]; }
		throw std::runtime_error("Memory Access Violation");
	}

	template<IntegralType T, size_t Rows> void Vector<T, Rows>::operator+=(const Vector<T, Rows>& other) {
		for(int i = 0; i < Rows; ++i) {
			data[i] += other[i];
		}
	}

	template<IntegralType T, size_t Rows> Vector<T, Rows> Vector<T, Rows>::operator+(const Vector<T, Rows>& other) const {
		Vector<T, Rows> retval(*this);
		retval += other;
		return retval;
	}

	template<IntegralType T, size_t Rows> void Vector<T, Rows>::operator*=(T t) {
		for(int i = 0; i < Rows; ++i) {
			data[i] *= t;
		}
	}

	template<IntegralType T, size_t Rows> Vector<T, Rows> Vector<T, Rows>::operator*(T t) const {
		Vector<T, Rows> retval(*this);
		retval *= t;
		return retval;
	}

	template<IntegralType T, size_t Rows> T Vector<T, Rows>::operator*(const Vector<T, Rows>& other) const {
		T retval = 0;
		for(int i = 0; i < Rows; ++i) {
			retval += data[i] * other[i];
		}
		return retval;
	}

}