#pragma once

namespace FloMath {

	const long double pi = 3.14159265358979323846;
	const long double e = 2.71828182845904523536;
	const long double inf = 1E308 * 1E308;
	const long double nan = inf * 0.0;

	const long double E() { return e; }
	const long double Pi() { return pi; }
	const long double Inf() { return inf; }
	const long double NaN() { return nan; }

}