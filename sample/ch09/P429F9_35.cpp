#include <iostream>      
#include "opencv2/opencv.hpp"
#include "utility/utility.hpp"
#include "algorithm/algorithm.hpp"

using namespace std;
using namespace cv;

int main(int argc, char*argv[])
{
	Mat src = imread("../data/DIP3E_Original_Images_CH09/Fig0935(a)(ckt_board_section).tif", 0);
	
	Mat se = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5));

	Mat b;
	erode(src, b, se);

	Mat c;
	dilate(src, c, se);

	imshow("a", src);
	imshow("b", b);
	imshow("c", c);
	
	
	waitKey();
	return 0;
}



