#include "dipl.h"
#include <matplot/matplot.h>
#include <numeric>

int main()
{
    cv::Mat gray = cv::imread("/Users/refantasy/Downloads/1.jpg", 0);
    //cv::Mat gray   = cv::imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH03/Fig0316(4)(bottom_left).tif", 0);


    //cv::imshow("src", gray);
    // cv::Mat hist_mat = GetHistogram(gray);
    // cv::imshow("hist", hist_mat);
    // cv::waitKey(1);

    auto hist = ComputeHistogram(gray, true);
    // cv::Mat h(res);
    std::cout << cv::Mat(hist) << std::endl;



    // // 构造横坐标 0..255
    // std::vector<double> x(256);
    // std::iota(x.begin(), x.end(), 0.0);
    //
    // // 转成 double（bar 接受 vector<double>）
    // std::vector<double> y(hist.begin(), hist.end());
    //
    // auto bar = matplot::bar(x, y);
    // bar->face_color("steelblue");
    // bar->line_width(1);
    //
    // matplot::title("Grayscale Histogram");
    // matplot::xlabel("Gray level");
    // matplot::ylabel("Count");
    // matplot::show();
    // auto h = matplot::hist(y, x);
    // matplot::show();
    //std::cout << "Histogram with " << h->num_bins() << " bins" << std::endl;
}
