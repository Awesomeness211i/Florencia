export module Calculus;

namespace FloMath {

	template<typename T>
	inline double DefiniteDerivative(T function, double x, double h) {
		return (function(x + h) - function(x)) / h;
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

	//use n for better accuracy (make it bigger)
	export template<typename T>
	inline double Integral(double a, double b, T function, int n = 1000) {
		return DefiniteIntegral(a, b, function, n);
	}

	//use h for better accuracy (make it smaller)
	export template<typename T>
	inline double Derivative(T function, double x, double h = 0.001) {
		return DefiniteDerivative(function, x, h);
	}

}