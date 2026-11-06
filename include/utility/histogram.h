#pragma once
#include "opencv2/opencv.hpp"
#include <vector>
using namespace cv;

std::vector<int> ComputeHistogram(const cv::Mat& gray_image);

cv::Mat DrawHistogram(std::vector<int> hist,
                      cv::Scalar       fg   = cv::Scalar(0, 0, 0),
                      cv::Scalar       bg   = cv::Scalar(160, 160, 160),
                      int              n    = 2,
                      int              rows = 400);

cv::Mat ShowHistogram(const cv::Mat& gray_image, int delay = 0);
