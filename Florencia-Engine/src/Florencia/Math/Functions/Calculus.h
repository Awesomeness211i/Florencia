#pragma once
namespace FloMath {

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
