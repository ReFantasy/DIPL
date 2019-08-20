#ifndef __TIMER_H__
#define __TIMER_H__
#include <chrono>


using namespace std::chrono;

class Timer
{
public:
	Timer() :_is_stoped(true) {}
	void Start()
	{
		_start_time = high_resolution_clock::now();
	}
	

	void ReSet()
	{
		_start_time = high_resolution_clock::now();
	}

	template<typename T = milliseconds>
	int Elapse()const
	{
		return duration_cast<T>(high_resolution_clock::now() - _start_time).count();
	}
	~Timer() {}

private:
	high_resolution_clock::time_point _start_time;


	bool _is_stoped;
};

#endif//__TIMER_H__
