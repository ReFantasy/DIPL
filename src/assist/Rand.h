#ifndef __RAND_H__
#define __RAND_H__
#include <random>
#include <ctime>
template<typename T = int>
class Rand
{
public:
	Rand(T minv = std::numeric_limits<T>::min,
		T maxv = std::numeric_limits<T>::max) 
		:_min(minv), _max(maxv) , d(std::uniform_real_distribution<T>(minv, maxv))
	{
		e.seed(std::time(nullptr));
	}

	T Random()
	{
		
		return d(e);
	}

	T operator()()
	{
		return d(e);
	}

	~Rand() {}
	

private:
	std::default_random_engine e;
	std::uniform_real_distribution<T> d;
	T _min;
	T _max;
};

#endif//__RAND_H__

