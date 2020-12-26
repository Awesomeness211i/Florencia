#pragma once

namespace FloMath {
	
	template<typename T>
	T abs(T x) {
		if (x < 0) {
			return -x;
		}
		return x;
	}

	template<typename T>
	int floor(T x) {
		if (x < 0) {
			return (int)x - 1;
		}
		return (int)x;
	}

}