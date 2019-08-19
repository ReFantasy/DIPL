#include <iostream>      
#include <vector>
#include <iterator>
#include "opencv2/opencv.hpp"
#include "algorithm/Fourier.h"

using namespace std;
using namespace cv;

template<int _Ty = CV_8UC1>
void MatFourier(const Mat &img)
{
	cout << "default:" << CV_8UC1 << endl;
}

template<>
void MatFourier<CV_64FC1>(const Mat &img)
{
	cout << "CV_64FC1" << endl;
}

int main()
{
	Mat src(100, 100, CV_8UC1);

	MatFourier<CV_64FC1>(src);

	system("pause");
	return 0;
}