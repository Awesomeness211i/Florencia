export module Declarations;

namespace FloMath {

	constexpr long double pi = 3.14159265358979323846;
	constexpr long double e = 2.71828182845904523536;

	export {
		constexpr long double E() { return e; }
		constexpr long double Pi() { return pi; }
		constexpr long double Inf() { return 1E308 * 1E308; }
		constexpr long double NaN() { return Inf() * 0.0; }
	}

}