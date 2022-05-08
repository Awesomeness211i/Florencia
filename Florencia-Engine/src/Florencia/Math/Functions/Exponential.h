#pragma once
#include <math.h>
#include "../Declarations.h"

namespace FloMath {

	//index determines accuracy of computation
	template<typename T, unsigned index = 5>
	T ln(T x) {
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

	template<int base = 10, typename T>
	T log(T x) {
		if (base != 1) { return (FloMath::ln(x) / FloMath::ln(base)); }
		return Inf();
	}
}