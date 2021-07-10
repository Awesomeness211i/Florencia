module;
#include <chrono>
export module Timestep;

namespace Florencia {

	class TimePoint {
	public:
		TimePoint() { m_TimePoint = m_Clock.now(); }
		auto Get() const { return m_TimePoint; }
		auto operator-(const TimePoint& other) const { return m_TimePoint - other.m_TimePoint; }
	private:
		std::chrono::high_resolution_clock m_Clock;
		std::chrono::high_resolution_clock::time_point m_TimePoint;
	};

	export class Time {
	public:
		//Gets current time at creation
		Time(TimePoint time = TimePoint()) : m_TimePoint(time) {}
		TimePoint GetTimePoint() const { return m_TimePoint; }
	private:
		TimePoint m_TimePoint;
	};

	export class Timestep {
	public:
		//Seconds By Default
		Timestep(const Time start, const Time end) : m_Duration(end.GetTimePoint() - start.GetTimePoint()) {}
		operator double() { return GetSeconds(); }

		double GetSeconds() const { return GetMilliseconds() / 1000.0; } //1 second is 1000 milliseconds
		double GetMilliseconds() const { return GetMicroseconds() / 1000.0; } //1 millisecond is 1000 microseconds
		double GetMicroseconds() const { return GetNanoseconds() / 1000.0; } //1 microsecond is 1000 nanoseconds
		double GetNanoseconds() const { return (double)m_Duration.count(); } //1 nanosecond is 1 nanosecond
	private:
		//Duration in nanoseconds to keep accurate time
		std::chrono::nanoseconds m_Duration;
	};

}