#pragma once

namespace FloMath {

	template<typename T, unsigned Dim>
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
			if (index < Dim)
				return data[index];
			//throw;
		}
	private:
		T data[Dim];
	};

}