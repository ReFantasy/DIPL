#include "image_convert.h"
#include "iostream"
#include "spatial_filter.h"
#include <histogram.h>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

int main()
{

    cv::Mat a   = cv::imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH03/Fig0316(4)(bottom_left).tif", 0);
    auto    src = IPL::HistogramEqualizate(IPL::Mat2Vector2D(a));
    auto    dst = IPL::HistogramEqualizate(src);
    auto    b   = IPL::Vector2D2Mat(dst);

    auto a_hist = GetHistogram(a);
    auto b_hist = GetHistogram(b);

    cv::imshow("a", a);
    cv::imshow("b", b);
    cv::imshow("a_hist", a_hist);
    cv::imshow("b_hist", b_hist);
    cv::waitKey();
}
