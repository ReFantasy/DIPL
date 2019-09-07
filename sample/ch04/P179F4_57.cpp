#include <iostream>      
#include <vector>
#include "opencv2/opencv.hpp"

#include "algorithm/algorithm.hpp"
#include "utility/utility.hpp"



using namespace std;


int main(int argc, char *argv[])
{
	std::string image_path = "../data/DIP3E_Original_Images_CH04/Fig0457(a)(thumb_print).tif";
	Mat src = imread(image_path, 0);
	
	int old_rows = src.rows;
	int old_cols = src.cols;
	// 寻找最佳图像尺寸
	int optimal_rows = IPL::Nearst2Power(src.rows);
	int optimal_cols = IPL::Nearst2Power(src.cols);
	resize(src, src, { optimal_cols,optimal_rows });

	// 生成滤波核
	auto kernel_fft = IPL::BHPF(src.rows, src.cols, 50, 4);


	IPL::Fourier fourier;
	auto _src_fourier = IPL::Mat2CentreVector2D(src);
	auto src_fourier = fourier.FFT(_src_fourier);
	for (int i = 0; i < optimal_rows; i++)
	{
		for (int j = 0; j < optimal_cols; j++)
		{
			src_fourier[i][j] *= kernel_fft[i][j];
		}
	}

	auto _dst = fourier.IFFT(src_fourier);
	for (int i = 0; i < optimal_rows; i++)
	{
		for (int j = 0; j < optimal_cols; j++)
		{
			_dst[i][j] *= pow(-1, i + j);
		}
	}

	Mat b(optimal_rows, optimal_cols, CV_8UC1);
	for (int i = 0; i < optimal_rows; i++)
	{
		for (int j = 0; j < optimal_cols; j++)
		{
			int v = _dst[i][j].real();
			if (v > 255)v = 255;
			if (v < 0) v = 0;
			b.data[i*optimal_cols+j] = v;
		}
	}

	Mat c(optimal_rows, optimal_cols, CV_8UC1);
	for (int i = 0; i < optimal_rows; i++)
	{
		for (int j = 0; j < optimal_cols; j++)
		{
			int v = _dst[i][j].real();
			if (v > 0)v = 255;
			if (v < 0) v = 0;
			c.data[i*optimal_cols + j] = v;
		}
	}

	

	resize(b, b, { old_cols,old_rows });
	resize(c, c, { old_cols,old_rows });
	




	imshow("a", src);
	
	imshow("b", b);
	imshow("c", c);

	waitKey();
	return 0;
}




