#include <iostream>      
#include "opencv2/opencv.hpp"
#include "utility/utility.hpp"
#include "algorithm/algorithm.hpp"



using namespace std;
using namespace cv;

int main(int argc, char*argv[])
{
	Mat src = imread("../data/DIP3E_Original_Images_CH09/Fig0911(a)(noisy_fingerprint).tif", 0);
	imshow("a", src);


	Mat se = getStructuringElement(cv::MORPH_RECT, { 3,3 });
	cout  << se << endl;
	

	Mat c;
	cv::erode(src, c, se);
	imshow("c", c);

	Mat d;
	cv::dilate(c, d, se);
	imshow("d", d);

	Mat e;
	cv::dilate(d, e, se);
	imshow("e", e);

	Mat f;
	cv::erode(e, f, se);
	imshow("f", f);

	
	waitKey();
	return 0;
}

