/************************************************************************
 *
 *  自定义图像类型与OpenCV图像类型转换
 *
 ***********************************************************************/
#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <vector>
#include <string>
#include "../algorithm/Fourier.h"
#include "../algorithm/GaussKernel.h"
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

constexpr int N = 4;
class Gauss
{
	using Complex2D = vector<vector<std::complex<double>>>;
public:
	Gauss() = default;
	Gauss(int rows, int cols, double A, double sigma_x, double sigma_y);
	void SetKernel(const vector<vector<double>> &gauss_array);
	vector<vector<std::complex<double>>> operator()(const vector<vector<std::complex<double>>> &fourier);

private:
	vector<vector<double>> _gauss_array;
	
};
// 傅里叶滤波
class FourierFilter
{
	using Complex2D = vector<vector<std::complex<double>>>;
	struct default_op
	{
		Complex2D operator()(const Complex2D &op)
		{
			return op;
		}
	};
public:
	FourierFilter() = default;
	Mat operator()(const Mat &src, std::function<Complex2D(Complex2D)> op = default_op{});

private:
	vector<vector<double>> ImageData(const Mat &img);
	vector<vector<double>> ConvertToImage(const Complex2D&);
	Mat Out8UC1(const vector<vector<double>> &d);

private:
	Fourier fourier;
	vector<vector<std::complex<double>>> _src_fourier_res;
	vector<vector<std::complex<double>>> _dst_fourier_res;

};


#endif//__IMAGE_H__