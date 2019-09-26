#ifndef __WAVELET_TRANSFORM_H__
#define __WAVELET_TRANSFORM_H__
#include "algorithm.hpp"
#include <vector>
namespace IPL
{
	// 上采样
	template<typename T>
	std::vector<std::vector<T>> PryUp(const std::vector<std::vector<T>> &src)
	{
		auto res = PryUpByRow(src);
		res = PryUpByCol(res);
		return res;
	}
	
	template<typename T>
	std::vector<std::vector<T>> PryUpByRow(const std::vector<std::vector<T>> &src)
	{
		int rows = src.size() * 2;
		int cols = src[0].size();
		auto res = std::vector<std::vector<T>>(rows, std::vector<T>(cols, T{}));
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if ((i % 2 == 0) && (j % 2 == 0))
				{
					res[i][j] = src[i / 2][j];
				}
				else
				{
					res[i][j] = T{};
				}
			}
		}

		return res;
	}
	
	template<typename T>
	std::vector<std::vector<T>> PryUpByCol(const std::vector<std::vector<T>> &src)
	{
		int rows = src.size();
		int cols = src[0].size() * 2;
		auto res = std::vector<std::vector<T>>(rows, std::vector<T>(cols, T{}));
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if ((i % 2 == 0) && (j % 2 == 0))
				{
					res[i][j] = src[i][j / 2];
				}
				else
				{
					res[i][j] = T{};
				}
			}
		}

		return res;
	}

	// 下采样
	template<typename T>
	std::vector<std::vector<T>> PryDown(const std::vector<std::vector<T>> &src)
	{
		auto res = PryDownByRow(src);
		res = PryDownByCol(res);
		return res;
	}

	template<typename T>
	std::vector<std::vector<T>> PryDownByRow(const std::vector<std::vector<T>> &src)
	{
		int rows = src.size();
		int cols = src[0].size();

		//auto res = IPL::MakeVector2D(rows / 2, cols);
		auto res = std::vector<std::vector<T>>(rows / 2, std::vector<T>(cols, T{}));

		for (int i = 0; i < res.size(); i++)
		{
			for (int j = 0; j < res[0].size(); j++)
			{

				res[i][j] = src[i * 2][j];
			}
		}

		return res;
	}

	template<typename T>
	std::vector<std::vector<T>> PryDownByCol(const std::vector<std::vector<T>> &src)
	{
		int rows = src.size();
		int cols = src[0].size();

		//auto res = IPL::MakeVector2D(rows, cols / 2);
		auto res = std::vector<std::vector<T>>(rows, std::vector<T>(cols / 2, T{}));

		for (int i = 0; i < res.size(); i++)
		{
			for (int j = 0; j < res[0].size(); j++)
			{

				res[i][j] = src[i][j * 2];
			}
		}

		return res;
	}

	void PyramidExample(const std::vector<std::vector<double>> &src, std::vector<std::vector<double>> &approximate, 
		std::vector<std::vector<double>> &residual);


    // 哈尔基函数
	class HaarBasis
	{
	public:
		HaarBasis(int k, int p, int q, int N);
		double operator()(double z);
	private:
		int _k;
		int _p;
		int _q;
		int _N;
		double _div_sqrt_N;

	};


}



#endif//__WAVELET_TRANSFORM_H__