#pragma once
#include "../Constants.h"
#include <math.h>
/* TODO: Implement a version of pow() either with function notation or with ^ notation */
namespace FloMath {

	/*template<typename T>
	T ln(T x, int index = 10) {
		double sum = 0.0;
		double top = (x - 1.0) / (x + 1.0);
		int bottom = 0;
		if (x > 0) {
			for (int i = 1; i <= index; i++) {
				bottom = 2*i-1;
				sum += (pow(top, bottom)) / bottom;
			}
			return (T)(2 * sum);
		}
		return nan;
	}

	template<double base = 10, typename T>
	T log(T x, int index = 10) {
		if (base != 1) {
			return (ln(x, index) / ln(base, index));
		}
		return nan;
	}

	//only for integer powers
	double pow(double x, int p) {
		if (p > 0) {
			for (int i = 1; i < p; i++) {
				x *= x;
			}
			return x;
		}
		if (p < 0) {
			double temp = x;
			for (int i = 1; i < -p; i++) {
				x /= temp;
			}
			return x;
		}
		return nan;
	}*/

}