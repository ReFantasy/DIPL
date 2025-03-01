#include "ipl.h"
using namespace cv;
using namespace std;

int main(int argc, char*argv[])
{
	Mat src = imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH09/Fig0935(a)(ckt_board_section).tif", 0);
	
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



