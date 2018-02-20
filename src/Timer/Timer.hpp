#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
	using high_resolution_clock = std::chrono::high_resolution_clock;
	using milliseconds = std::chrono::milliseconds;
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

	milliseconds Elapsed() const
	{
		return std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - start);
	}

	friend std::ostream& operator<<(std::ostream& out, const Timer& timer)
	{
		return out << timer.Elapsed().count();
	}
private:
	high_resolution_clock::time_point start;
};
	
#endif // TIMER_HPP