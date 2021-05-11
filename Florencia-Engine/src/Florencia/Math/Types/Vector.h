#pragma once
#include <stdexcept>

namespace FloMath {

	template<typename T, size_t Rows>
	class Vector {
	public:
		template<typename... Args>
		Vector(Args... args)
			:data{args...}
		{}
		T& operator[](unsigned index) {
			return data[index];
		}
		T& at(unsigned index) {
			if (index < Rows)
				return data[index];
			throw std::runtime_error("Memory Access Violation");
		}
	private:
		T data[Rows];
	};

}