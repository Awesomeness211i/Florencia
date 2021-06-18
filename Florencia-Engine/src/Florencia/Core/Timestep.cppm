export module Timestep;
import <chrono>;

export namespace Florencia {

	using Clock = std::chrono::high_resolution_clock;

	class Time {
	public:
		Time(Clock::time_point time) : m_Time(time) {}
		Clock::time_point GetTime() const { return m_Time; }
	private:
		Clock::time_point m_Time;
	};

	class Timestep {
	public:
		//seconds by default
		Timestep(const Time start, const Time end) : m_Duration(end.GetTime() - start.GetTime()) {}
		operator double() { return GetSeconds(); }

		double GetSeconds() const { return m_Duration.count() / 1000000000.0; } //1 second in 1000000000 nanoseconds
		double GetMilliseconds() const { return m_Duration.count() / 1000000.0; } //1 milliseconds is 1000000 nanoseconds
		double GetMicroseconds() const { return m_Duration.count() / 1000.0; } //1 microseconds in 1000 nanoseconds
		double GetNanoseconds() const { return m_Duration.count(); } //1 nanosecond in 1 nanosecond
	private:
		std::chrono::nanoseconds m_Duration;
	};

}