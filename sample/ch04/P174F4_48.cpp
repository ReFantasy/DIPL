#include <iostream>      
#include <vector>
#include "opencv2/opencv.hpp"

#include "algorithm/algorithm.hpp"
#include "utility/utility.hpp"



using namespace std;
Mat GLPFExampel(const Mat &src, double D0)
{
	assert(src.type() == CV_8UC1);

	// 初始化变量和数据
	IPL::FourierFilter fourier_filter;

	Mat src_fft;
	src.copyTo(src_fft);
	int old_rows = src_fft.rows;
	int old_cols = src_fft.cols;
	// 寻找最佳图像尺寸
	int optimal_rows = IPL::Nearst2Power(src_fft.rows);
	int optimal_cols = IPL::Nearst2Power(src_fft.cols);
	resize(src_fft, src_fft, { optimal_cols,optimal_rows });

	// 生成滤波核
	auto kernel_fft = IPL::GLPF(src_fft.rows, src_fft.cols, D0);


	Mat dst = fourier_filter(src_fft, kernel_fft);
	

	resize(dst, dst, { old_cols,old_rows });
	return dst;
}


int main(int argc, char *argv[])
{
	std::string image_path = "../data/DIP3E_Original_Images_CH04/Fig0442(a)(characters_test_pattern).tif";
	Mat src = imread(image_path, 0);
	
	auto b = GLPFExampel(src, 10);
	auto c = GLPFExampel(src, 30);
	auto d = GLPFExampel(src, 60);
	auto e = GLPFExampel(src, 160);
	auto f = GLPFExampel(src, 460);

	imshow("a", src);
	imshow("b", b);
	imshow("c", c);
	imshow("d", d);
	imshow("e", e);
	imshow("f", f);

	waitKey();
	return 0;
}




