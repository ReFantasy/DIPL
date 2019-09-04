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



int main(int argc, char *argv[])
{	
	std::string image_path = "../data/DIP3E_Original_Images_CH04/Fig0424(a)(rectangle).tif";
	Mat src = imread(image_path, 0);
	
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



