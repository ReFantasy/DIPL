#include <iostream>      
#include <vector>
#include "opencv2/opencv.hpp"

#include "algorithm/algorithm.hpp"
#include "utility/utility.hpp"



using namespace std;


int main(int argc, char *argv[])
{
	Mat a = imread("../data/DIP3E_Original_Images_CH05/Fig0507(a)(ckt-board-orig).tif", 0);
	Mat b = imread("../data/DIP3E_Original_Images_CH05/Fig0507(b)(ckt-board-gauss-var-400).tif", 0);
	auto c = IPL::MeanBlurArithmetic(b, 3);
	auto d = IPL::MeanBlurGeometry(b, 3);

	imshow("a", a);
	imshow("b", b);
	imshow("c", c);
	imshow("d", d);

	waitKey();
	return 0;
}




