#pragma once
#include "../Declarations.h"
#include "Other.h"
/*
TODO: Make the trigonometric functions arcsin() arccos() arctan()
*/
namespace FloMath {

	//In radians
	template<typename T>
	inline T cos(T x) noexcept {
		constexpr T tp = 1. / (2. * pi);
		x *= tp;
		x -= T(.25) + floor(x + T(.25));
		x *= T(16.) * (abs(x) - T(.5));
		x += T(.225) * x * (abs(x) - T(1.));
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
		return cos(x - pi / 2);
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
