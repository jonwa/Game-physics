#include <chrono>

class Timer
{
public:
	Timer()
	{
		start();
	}

	void start()
	{
		start_ = std::chrono::steady_clock::now();
	}

	int elapsed_milliseconds()
	{
		auto now = std::chrono::steady_clock::now();
		auto diff = now - start_;
		millisecs_t duration(std::chrono::duration_cast<millisecs_t>(diff));
		return duration.count();
	}
private:
	typedef std::chrono::duration<int, std::milli> millisecs_t;
	std::chrono::steady_clock::time_point start_;
};