#pragma once

namespace util {

	class Timer
	{
	public:
		Timer();
		~Timer();

		inline void reset() { m_currentNanoseconds = getProgramNanoseconds(); }

		inline unsigned long long getPassedNanoseconds() const { return getProgramNanoseconds() - m_currentNanoseconds; }
		inline double getPassedSeconds() const { return getPassedNanoseconds() / 1000000000.0; }

		static unsigned long long getProgramNanoseconds();
	private:
		unsigned long long m_currentNanoseconds;
	};

}