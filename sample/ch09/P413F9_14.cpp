#include <iostream>      
#include "opencv2/opencv.hpp"
#include "utility/utility.hpp"
#include "algorithm/algorithm.hpp"



using namespace std;
using namespace cv;

int main(int argc, char*argv[])
{
	Mat src = imread("../data/DIP3E_Original_Images_CH09/Fig0914(a)(licoln from penny).tif", 0);
	imshow("a", src);


	Mat se = getStructuringElement(cv::MORPH_RECT, { 3,3 });
	cout  << se << endl;

	Mat src_ero;
	cv::erode(src, src_ero, se);

	Mat b = src - src_ero;
	imshow("b", b);

	
	waitKey();
	return 0;
}

