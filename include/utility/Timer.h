#ifndef __TIMER_H__
#define __TIMER_H__
#include <chrono>

using namespace std::chrono;

class Timer
{
public:
    Timer() : _is_stoped(true) {}
    void Start() { _start_time = high_resolution_clock::now(); }

    void ReSet()
    {
        suspends.clear();
        _start_time = high_resolution_clock::now();
    }

    void Suspend() { _suspend_time = high_resolution_clock::now(); }
    void Continue()
    {
        auto current_time = high_resolution_clock::now();
        suspends.push_back(std::make_pair(_suspend_time, current_time));
    }

    template<typename T = milliseconds>
    int Elapse() const
    {
        int total_suspend_time = 0;
        for (auto& suspend : suspends)
        {
            total_suspend_time += duration_cast<T>(suspend.second - suspend.first).count();
        }
        return duration_cast<T>(high_resolution_clock::now() - _start_time).count() - total_suspend_time;
    }
    ~Timer() {}

private:
    high_resolution_clock::time_point _start_time;
    high_resolution_clock::time_point _suspend_time;

    std::vector<std::pair<high_resolution_clock::time_point, high_resolution_clock::time_point>> suspends;

    bool _is_stoped;
};

#endif //__TIMER_H__
