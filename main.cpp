#include <iostream>
#include "Image/image.h"
using namespace std;

int main()
{
	//IPL::Image<double> img = IPL::imread("0", IPL_8UC1);
	//img1.Print();

	IPL::Image img(600, 600, PixType::IPL_8UC1);
	system("pause");
	return 0;
}