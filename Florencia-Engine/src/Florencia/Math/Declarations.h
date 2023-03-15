#pragma once
#include <math.h>

namespace FloMath {

	inline const long double E() { return 2.71828182845904523536; }
	inline const long double Pi() { return 3.14159265358979323846; }
	inline const long double Inf() { return 1E308*1E308; }
	inline const long double NaN() { return Inf() * 0.0; }

	inline int roundoff(auto x) { return (int)x; }

	//first happens if statement in parentheses is true else second happens
	inline auto abs(auto x) { return (x < 0) ? -x : x; }

	inline int ceil(auto x) { return (x <= 0) ? roundoff(x) : roundoff(x) + 1; }

	inline int floor(auto x) { return (x < 0) ? roundoff(x) - 1 : roundoff(x); }

	//uses information I have to get rid of unnecessary checks from ceil and floor functions
	inline int round(auto x) {
		return (x < 0) ?
			//x < 0 case: (abs(x) - floor(x) >= 0.5) ? floor(x) : ceil(x);
			(-x - roundoff(-x) >= 0.5) ? roundoff(x) - 1 : roundoff(x)
			//x >= 0 case: (abs(x) - floor(x) >= 0.5) ? ceil(x) : floor(x);
			: (x - roundoff(x) >= 0.5) ? roundoff(x) + 1 : roundoff(x);
	}

	//In radians
	template<typename T>
	inline T cos(T x) noexcept {
		const T tp = 1.0 / (2.0 * Pi());
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

	//index determines accuracy of computation
	template<typename T, unsigned index = 5>
	inline T ln(T x) {
		double sum = 0.0;
		double top = (x - 1.0) / (x + 1.0);
		double bottom = 0;
		if (x > 0) {
			for (int i = 1; i <= index; i++) {
				bottom = 2*i-1;
				sum += (pow(top, bottom)) / bottom;
			}
			return (T)(2 * sum);
		}
		return NaN();
	}

	template<int base = 10, unsigned index = 5, typename T>
	inline T log(T x) {
		if (base != 1) { return (FloMath::ln<T, index>(x) / FloMath::ln<T, index>(base)); }
		return Inf();
	}

	template<typename T>
	inline double DefiniteDerivative(T function, double x, double h = 0.01) {
		return (function(x + h) - function(x - h)) / (2 * h);
	}

	template<typename T>
	inline double DefiniteIntegral(double a, double b, T function, int n) {
		double result = 0.0;
		double delta = (b - a) / n;
		if (a == b) { return 0.0; }
		for (int i = 0; i <= n; i++) {
			result += function(a + delta * i) * delta;
		}
		return result;
	}

}