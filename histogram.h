#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__
#include <vector>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

// gray_image 灰度图像
// L 灰度级
vector<int> GetHistogram(const Mat &gray_image, int L = 256);


// gray_image 灰度图像
void ShowHistogram(std::string name,const Mat &gray_image, int Height = 255);

#endif//__HISTOGRAM_H__
