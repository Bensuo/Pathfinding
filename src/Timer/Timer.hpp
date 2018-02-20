#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
	using high_resolution_clock = std::chrono::high_resolution_clock;
	using nanoseconds = std::chrono::nanoseconds;
public:
	explicit Timer(bool run = false)
	{
		if (run)
		{
			Reset();
		}
	}

	void Reset()
	{
		start = high_resolution_clock::now();
	}

	nanoseconds Elapsed() const
	{
		return std::chrono::duration_cast<nanoseconds>(high_resolution_clock::now() - start);
	}

	friend std::ostream& operator<<(std::ostream& out, const Timer& timer)
	{
		return out << timer.Elapsed().count() / 1000000.0;
	}
private:
	high_resolution_clock::time_point start;
};
	
#endif // TIMER_HPP