#include "iostream"
#include "dipl.h"

int main()
{

    cv::Mat a   = cv::imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH03/Fig0316(4)(bottom_left).tif", 0);
    auto    src = IPL::HistogramEqualization(IPL::Mat2Vector2D(a));
    auto    dst = IPL::HistogramEqualization(src);
    auto    b   = IPL::Vector2D2Mat(dst);

    auto a_hist = GetHistogram(a);
    auto b_hist = GetHistogram(b);

    cv::imshow("a", a);
    cv::imshow("b", b);
    cv::imshow("a_hist", a_hist);
    cv::imshow("b_hist", b_hist);
    cv::waitKey();
}
