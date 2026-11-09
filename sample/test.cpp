#include "dipl.h"
#include <opencv2/core/types.hpp>

int main()
{
    // cv::Mat gray = cv::imread("/Users/refantasy/Downloads/1.jpg", 0);
    cv::Mat gray   = cv::imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH03/Fig0316(4)(bottom_left).tif",0);

    // auto hist = ComputeHistogram(gray);
    // auto img = DrawHistogram(hist);
    // cv::imshow("img", img);
    // cv::waitKey();

    ShowHistogram(gray, 0);
}
