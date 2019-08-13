#ifndef __FILTER_H__
#define __FILTER_H__
#include "Image.h"

// 拉普拉斯滤波
class Laplace
{
public:
	Image operator()(const Image &img);
};


class BoxFilter
{
public:
	BoxFilter();
	~BoxFilter();
};

#endif//__FILTER_H__

