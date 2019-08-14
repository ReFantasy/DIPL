#include <iostream>
#include "opencv2/opencv.hpp"
#include "Fourier.h"
using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
	//Mat src = imread("C:\\Users\\30974\\Desktop\\flower.jpg", 0);
	Fourier fourier;
	vector<vector<double>> a{ {1,2},{3,4} };

	auto res = fourier.DFT(a);
	fourier.IDFT(res);

	system("pause");
	return 0;
}