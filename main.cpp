#include <iostream>      
#include <vector>
#include <iterator>
#include <random>
#include <chrono>
#include "opencv2/opencv.hpp"
#include "algorithm/Fourier.h"
#include "image/Image.h"
#include "Rand.h"
#include <share.h>
#include "Timer.h"

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


int main()
{
	Timer timer;
	Fourier fourier;
	Rand<double> _rand(1, 10);

	

	Mat src = imread("1.tif", 0);
	int rows = src.rows;
	int cols = src.cols;
	vector<vector<double>> img(rows, vector<double>(cols, 0));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			img[i][j] = src.data[i*cols + j];// *pow(-1, i + j);
		}
	}

	auto dft_img = fourier.DFT(img);

	// 频谱
	vector<vector<double>> pu(rows, vector<double>(cols, 0));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			pu[i][j] = std::abs(dft_img[i][j]);
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			src.data[i*cols + j] = log(1+abs(pu[i][j]));
		}
	}

	imshow("src", src);
	waitKey();
	system("pause");
	return 0;
}