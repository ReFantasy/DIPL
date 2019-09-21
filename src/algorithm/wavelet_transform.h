#ifndef __WAVELET_TRANSFORM_H__
#define __WAVELET_TRANSFORM_H__
#include "algorithm.hpp"
#include <vector>
namespace IPL
{
	// �ϲ���
	std::vector<std::vector<double>> PryUp(const std::vector<std::vector<double>> &src);

	// �²���
	std::vector<std::vector<double>> PryDown(const std::vector<std::vector<double>> &src);

	void PyramidExample(const std::vector<std::vector<double>> &src, std::vector<std::vector<double>> &approximate, std::vector<std::vector<double>> &residual);
}



#endif//__WAVELET_TRANSFORM_H__