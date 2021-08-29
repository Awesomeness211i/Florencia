export module Piecewise;

export namespace FloMath {

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
}