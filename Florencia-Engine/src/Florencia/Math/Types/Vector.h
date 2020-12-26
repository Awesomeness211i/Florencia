#pragma once

namespace FloMath {

	template<typename T, unsigned Dim>
	class Vector {
	public:
		T& operator[](int index) {
			if (index < Dim) {
				return data[index];
			}
			//return nullptr;
		}
	private:
		T data[Dim];
	};

}