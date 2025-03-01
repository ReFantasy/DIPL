#include "dipl.h"
using namespace cv;
using namespace std;

int main(int argc, char*argv[])
{
	Mat src = imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH09/Fig0940(a)(rice_image_with_intensity_gradient).tif", 0);
	
	Mat otsu;
	threshold(src, otsu, 0, 255, THRESH_BINARY + THRESH_OTSU);
	
	Mat c;
	Mat se = getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(81, 81));
	morphologyEx(src, c, MORPH_OPEN, se);

	Mat top_hat = src - c;

	Mat e;
	threshold(top_hat, e, 0, 255, THRESH_BINARY + THRESH_OTSU);

	imshow("a", src);
	imshow("b", otsu);
	imshow("c", c);
	imshow("d", top_hat);
	imshow("e", e);
	
	
	waitKey();
	return 0;
}



