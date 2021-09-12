export module Motion;
import TimeStep;
import FloMath;

namespace FloPhysics {

	export struct ObjectData {
		FloMath::Vec3<float> m_Acceleration;//m/s^2
		FloMath::Vec3<float> m_Velocity;//m/s
		double m_Mass = 0;//Kg
	};

	//Newtons: Kg*m/s^2
	export void ApplyForce(ObjectData& data, const FloMath::Vec3<float>& force, Florencia::TimeStep ts) {
		data.m_Velocity += force * ts / data.m_Mass;
	}

}