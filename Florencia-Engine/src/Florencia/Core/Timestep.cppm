export module Timestep;
import <chrono>;

export namespace Florencia {

	using Clock = std::chrono::high_resolution_clock;

	static Clock::time_point GetCurrentTime() { return Clock::now(); }

	class Time {
	public:
		Time(Clock::time_point time) : m_Time(time) {}
		Clock::time_point GetTime() const { return m_Time; }
	private:
		Clock::time_point m_Time;
	};

	class Timestep {
	public:
		Timestep(const Time start, const Time end) : m_Duration(end.GetTime() - start.GetTime()) {}

		//seconds by default
		operator double() { return GetSeconds(); }

		double GetSeconds() const { return m_Duration.count() / 1000000000.0; }//1000000000 nanoseconds in 1 second
		double GetMilliseconds() const { return m_Duration.count() / 1000000.0; }//1 seconds is 1000 millisecond
		double GetMicroseconds() const { return m_Duration.count() / 1000.0; }//1 second is 1000000 microseconds
		double GetNanoseconds() const { return m_Duration.count(); } //1000000000 nanoseconds per second
	private:
		std::chrono::nanoseconds m_Duration;
	};

}