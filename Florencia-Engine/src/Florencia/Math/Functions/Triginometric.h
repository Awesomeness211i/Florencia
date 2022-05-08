#pragma once
#include "../Declarations.h"
#include "Piecewise.h"

namespace FloMath {

	//In radians
	template<typename T>
	inline T cos(T x) noexcept {
		constexpr T tp = 1.0 / (2.0 * Pi());
		x *= tp;
		x -= T(0.25) + FloMath::floor(x + T(0.25));
		x *= T(16.0) * (FloMath::abs(x) - T(0.5));
		x += T(0.225) * x * (FloMath::abs(x) - T(1.0));
		return x;
	}

	//In radians
	template<typename T>
	inline T sec(T x) noexcept {
		return 1.0 / cos(x);
	}

	//In radians
	template<typename T>
	inline T sin(T x) noexcept {
		return cos(x - Pi() / 2);
	}

	//In radians
	template<typename T>
	inline T csc(T x) noexcept {
		return 1.0 / sin(x);
	}

	//In radians
	template<typename T>
	inline T tan(T x) noexcept {
		return sin(x) / cos(x);
	}

	//In radians
	template<typename T>
	inline T cotan(T x) noexcept {
		return 1.0 / tan(x);
	}

}