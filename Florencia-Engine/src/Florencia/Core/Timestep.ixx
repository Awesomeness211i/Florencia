export module TimeStep;
import <chrono>;

namespace Florencia {

	export class TimePoint {
	public:
		TimePoint() { m_TimePoint = std::chrono::high_resolution_clock::now().time_since_epoch(); }
		double Get() const { return m_TimePoint.count(); }
	private:
		std::chrono::duration<double, std::chrono::seconds::period> m_TimePoint;
	};

	export class TimeStep {
	public:
		//Seconds By Default
		TimeStep(const TimePoint start, const TimePoint end) : m_Duration(end.Get() - start.Get()) {}
		operator double() { return GetSeconds(); }

		double GetSeconds() const { return m_Duration.count(); } //1 second is 1000 milliseconds
		double GetMilliseconds() const { return GetSeconds() * 1000.0; } //1 millisecond is 1000 microseconds
		double GetMicroseconds() const { return GetMilliseconds() * 1000.0; } //1 microsecond is 1000 nanoseconds
		double GetNanoseconds() const { return GetMicroseconds() * 1000.0; } //1 nanosecond is 1 nanosecond
	private:
		std::chrono::duration<double, std::chrono::seconds::period> m_Duration;
	};

}