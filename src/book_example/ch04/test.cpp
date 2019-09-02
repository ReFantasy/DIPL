#include <iostream>      
#include <vector>
#include <iterator>
#include <random>
#include <chrono>
#include "opencv2/opencv.hpp"
#include "utility/fourier_filter.h"
#include "utility/Timer.h"
#include "utility/Rand.h"


using namespace std;
using namespace cv;

template<typename T>
void Print(const vector<vector<T>> &vt)
{
	for (const auto &e : vt)
	{
		for (const auto&i : e)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl;
	}
}
std::ostream& operator<<(std::ostream &os, const std::complex<double> &cd)
{
	os << "[" << cd.real() << "," << cd.imag() << "]";
	return os;
}




// 傅里叶滤波示例
void FourierFilterExampel(const Mat &src);

int main(int argc, char*argv[])
{
	if(argc<2)
		return -1;
	
	std::string filename(argv[1]);
	Mat src = imread(filename, 0);
	FourierFilterExampel(src);
	
	waitKey();
	system("pause");
	return 0;
}

void FourierFilterExampel(const Mat &src)
{
	assert(src.type() == CV_8UC1);

	// 初始化变量和数据
	Timer timer;
	Rand<double> _rand(1, 10);
	IPL::FourierFilter fourier_filter;

	
	// ------------------------------------- FFT ---------------------------------------
	cout << "fft" << endl;
	Mat src_fft;
	src.copyTo(src_fft);
	int old_rows = src_fft.rows;
	int old_cols = src_fft.cols;
	// 寻找最佳图像尺寸
	int optimal_rows = IPL::Nearst2Power(src_fft.rows);
	int optimal_cols = IPL::Nearst2Power(src_fft.cols);
	resize(src_fft, src_fft, { optimal_cols,optimal_rows });

	// 生成滤波核
	auto kernel_fft = IPL::GHPF(src_fft.rows, src_fft.cols, 160);

	timer.Start();
	Mat fft = fourier_filter(src_fft, kernel_fft);
	cout << "fft: " << timer.Elapse()<<" milliseconds" << endl;

	resize(fft, fft, { old_cols,old_rows });
	imshow("fft", fft);

	cout << endl;



	// ------------------------------------- DFT ---------------------------------------
	cout << "dft" << endl;
	Mat src_dft;
	src.copyTo(src_dft);
	// 生成滤波核
	auto kernel_dft = IPL::GHPF(src_dft.rows, src_dft.cols, 160);
	timer.ReSet();
	Mat dft = fourier_filter(src_dft, kernel_dft, 1);
	cout << "dft: " << timer.Elapse() << " milliseconds" << endl;
	imshow("dft", dft);
	
}

