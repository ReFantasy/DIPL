#include <cmath>
#include <string>
#include <exception>
#include "wavelet_transform.h"
#include "frequency_distribution.h"
#include "spatial_filter.h"

void IPL::PyramidExample(const std::vector<std::vector<double>> &src, std::vector<std::vector<double>> &approximate, std::vector<std::vector<double>> &residual)
{
	int rows = src.size();
	int cols = src[0].size();


	// 生成近似图
	auto s = IPL::BlurArithmetic(src, 5);
	approximate = PryDown(s);

	// 上采样并进行插值滤波
	// 上采样将上一步得到的图像approximate尺寸扩大两倍 扩大的像素间填充0
	// 插值滤波将像素为0的位置根据原图像approximate进行插值
	// 这里采用最近邻插值代替以上两个步骤
	auto indicate = IPL::NearestNeighborInterpolation(approximate, rows, cols);
	

	residual = IPL::MakeVector2D(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			residual[i][j] = src[i][j] - indicate[i][j];
		}
	}
}

IPL::HaarBasis::HaarBasis(int k, int p, int q, int N)
	:_k(k), _p(p), _q(q), _N(N)
{
	if (_k != std::pow(2, _p) + _q - 1)
		// throw std::invalid_argument("k != 2^p+1-1");
		throw std::string("k != 2^p+1-1");
	_div_sqrt_N = 1.0 / std::sqrt(_N);
}

double IPL::HaarBasis::operator()(double z)
{
	if (_k == 0)
		return _div_sqrt_N;

	if ((z >= (_q - 1) / std::pow(2, _p)) && (z < (_q - 0.5) / std::pow(2, _p)))
	{
		return std::pow(2, _p / 2.0)*_div_sqrt_N;
	}
	else if ((z >= (_q - 0.5) / std::pow(2, _p)) && (z < _q  /std::pow(2, _p)))
	{
		return -std::pow(2, _p / 2.0)*_div_sqrt_N;
	}
	else
	{
		return 0;
	}
}
