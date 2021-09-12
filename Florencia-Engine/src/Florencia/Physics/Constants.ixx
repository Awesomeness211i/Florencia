export module Constants;

namespace FloPhysics {

	constexpr double G = 6.674301E-11;//gravitational constant: m^3/(kg*s^2)
	constexpr double h = 6.62607015E-34;//plancks constant: J*s
	constexpr double c = 2.99792458E8;//speed of light: m/s

	constexpr double M = 5.9722E24;//mass of earth: Kg
	constexpr double R = 6.378137E6;//radius of earth: m
	constexpr double g = G * M/(R * R);//acceleration at surface of earth: m/s^2

}