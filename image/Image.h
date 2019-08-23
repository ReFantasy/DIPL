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
#include "../algorithm/frequency_filter.h"
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

namespace IPL
{
	// 傅里叶滤波
	class FourierFilter
	{
		using Complex2D = vector<vector<std::complex<double>>>;
		
	public:
		FourierFilter() = default;
		Mat operator()(const Mat &src, const vector<vector<double>> &gauss, int ft_type = 0);

	private:
		vector<vector<double>> ImageData(const Mat &img);
		vector<vector<double>> ConvertToImage(const Complex2D&);
		Mat Out8UC1(const vector<vector<double>> &d);

	private:
		Fourier fourier;
		vector<vector<std::complex<double>>> _src_fourier_res;
		vector<vector<std::complex<double>>> _dst_fourier_res;

		vector<vector<std::complex<double>>> filter(const vector<vector<std::complex<double>>> &fourier, const vector<vector<double>> &gauss);

	};

}
#endif//__IMAGE_H__