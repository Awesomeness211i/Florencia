export module Other;

namespace FloMath {

	export template<typename T>
	inline T abs(T x) {
		if (x < 0) { return -x; }
		return x;
	}

	export template<typename T>
	inline int floor(T x) {
		if (x < 0) { return (int)x - 1; }
		return (int)x;
	}

}