#pragma once

#include "opencv2/opencv.hpp"
#include <vector>
using namespace cv;

Mat GetHistogram(Mat grayImage);

std::vector<int> ComputeHistogram(const cv::Mat& gray_image, bool show = false);
