#include <iostream>      
#include "opencv2/opencv.hpp"
#include "utility/utility.hpp"
#include "algorithm/algorithm.hpp"



using namespace std;
using namespace cv;

int main(int argc, char*argv[])
{
	Mat src = imread("../data/DIP3E_Original_Images_CH09/Fig0907(a)(text_gaps_1_and_2_pixels).tif", 0);
	imshow("a", src);


	Mat se = getStructuringElement(cv::MORPH_CROSS, { 3,3 });
	cout  << se << endl;
	

	Mat c;
	cv::dilate(src, c, se);
	imshow("c", c);

	
	waitKey();
	return 0;
}

