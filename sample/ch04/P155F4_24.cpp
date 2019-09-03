#include <iostream>      
#include <vector>
#include <iterator>
#include <random>
#include <chrono>
#include "opencv2/opencv.hpp"
#include "utility/fourier_filter.h"
#include "utility/Timer.h"
#include "utility/Rand.h"
#include "utility/image_convert.h"
#include "algorithm/Fourier.h"

using namespace std;

void OpencvFouier(Mat srcImage);

int main(int argc, char *argv[])
{
	
	//std::string image_path = "../data/DIP3E_Original_Images_CH04/1.tif";
	Mat src = imread(argv[1], 0);

	int rows = src.rows;
	int cols = src.cols;
	IPL::Fourier fourier;

	auto img = vector<vector<double>>(rows, vector<double>(cols, 0));
	auto img_centre = vector<vector<double>>(rows, vector<double>(cols, 0));
	
	img = IPL::Mat2Vector2D(src);
	img_centre = IPL::Mat2CentreVector2D(src);


	auto fres = IPL::Fourier::FFT(img);
	auto fres_centre = IPL::Fourier::FFT(img_centre);

	Mat b(rows, cols, CV_64FC1);
	for (int i = 0; i < rows; i++)
		for (int j = 1; j < cols; j++)
		{
			double tmp = abs(fres[i][j]);
			b.at<double>(i, j) = tmp;
		}
	normalize(b, b, 0, 1, NORM_MINMAX);

	Mat c(rows, cols, CV_64FC1);
	for (int i = 0; i < rows; i++)
		for (int j = 1; j < cols; j++)
		{
			double tmp = abs(fres_centre[i][j]);
			c.at<double>(i, j) = tmp;
		}
	normalize(c, c, 0, 1, NORM_MINMAX);


	Mat d(rows, cols, CV_8UC1);
	for (int i = 0; i < rows; i++)
		for (int j = 1; j < cols; j++)
		{
			double tmp =log(1 + abs(fres_centre[i][j]));
			d.data[i*cols + j] = tmp;
		}
	

	imshow("a", src);
	imshow("b", b);
	imshow("c", c);
	imshow("d", d);
	
	waitKey();
	return 0;
}

void OpencvFouier(Mat srcImage)
{
	// 2.将输入图像延扩到最佳尺寸，边界用0补充
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);
	// 将添加的像素初始化为0。
	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	// 3.为傅里叶变换的结果（实部和虚部）分配空间。
	// 将planes数组组合合并成一个多通道的数组complexI
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(),CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);

	// 4.进行离散傅里叶变换
	dft(complexI, complexI);

	// 5.将复数转换为幅值，即 log(1+sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
	split(complexI, planes);    //将多通道数组complexI分离成几个单通道数组，[0]=Re,[1]=Im
	magnitude(planes[0], planes[1], planes[0]); //planes[0] = magnitude
	Mat magnitudeImage = planes[0];

	// 6.进行对数尺度（logarithmic scale）缩放
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);    //求自然对数

	// 7.剪切和重分布幅度图象限
	//若有奇数行或奇数列，进行频谱裁剪
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));

	// 重新排列傅里叶图像中的象限，使得原点位于图像中心
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy));     //ROI区域的左上
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));    //ROI区域的右上
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));    //ROI区域的左下
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));   //ROI区域的右下
	//交换象限（左上与右下进行交换）
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	//交换象限（右上与左下进行交换）
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	// 8.归一化，用0到1之间的浮点值将矩阵变换为可视化的图像格式
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

	// 9.显示效果图
	imshow("OpenCV 频谱幅值", magnitudeImage);
}

