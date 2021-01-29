#pragma once

namespace FloMath {

	template<typename T, unsigned Rows>
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
			//throw;
		}
	private:
		T data[Rows];
	};

}