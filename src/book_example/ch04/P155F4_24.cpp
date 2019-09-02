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
	if (argc < 2)
		return -1;
	Mat src = imread(argv[1], 0);
	int rows = src.rows;
	int cols = src.cols;
	IPL::Fourier fourier;

	auto img = vector<vector<double>>(rows, vector<double>(cols, 0));
	for (int i = 0; i < rows; i++)
		for (int j = 1; j < cols; j++)
		{
			img[i][j] = src.data[i*cols + j] * pow(-1, i + j);
		}


	auto fres = IPL::Fourier::DFT(img);

	Mat c(rows, cols, CV_8UC1);
	for (int i = 0; i < rows; i++)
		for (int j = 1; j < cols; j++)
		{
			int tmp =sqrt(fres[i][j].real()*fres[i][j].real()+ fres[i][j].imag()*fres[i][j].imag());
			tmp = tmp < 0 ? 0 : tmp;
			tmp = tmp > 255 ? 255 : tmp;
			c.data[i*cols + j] = tmp;
			//c.at<double>(i, j) = abs(fres[i][j]);
		}
	//normalize(c, c, 0, 1);

	Mat d(rows, cols, CV_8UC1);
	for(int i = 0;i<rows;i++)
		for (int j = 1; j < cols; j++)
		{
			int tmp = 1 + log(abs(fres[i][j]));
			tmp = tmp < 0 ? 0 : tmp;
			tmp = tmp > 255 ? 255 : tmp;
			d.data[i*cols + j] = tmp;
		}
	
	imshow("c", c);
	imshow("d", d);

	
	waitKey();
	return 0;
}