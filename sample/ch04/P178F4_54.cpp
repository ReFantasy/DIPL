#include <vector>

#include "dipl.h"
using namespace cv;

using namespace std;
Mat IHPFExampel(const Mat &src, double D0)
{
    assert(src.type() == CV_8UC1);

    // 初始化变量和数据
    IPL::FourierFilter fourier_filter;

    Mat src_fft;
    src.copyTo(src_fft);
    int old_rows = src_fft.rows;
    int old_cols = src_fft.cols;
    // 寻找最佳图像尺寸
    int optimal_rows = IPL::Nearst2Power(src_fft.rows);
    int optimal_cols = IPL::Nearst2Power(src_fft.cols);
    resize(src_fft, src_fft, {optimal_cols, optimal_rows});

    // 生成滤波核
    auto kernel_fft = IPL::IHPF(src_fft.rows, src_fft.cols, D0);

    Mat dst = fourier_filter(src_fft, kernel_fft);

    resize(dst, dst, {old_cols, old_rows});
    return dst;
}

int main(int argc, char *argv[])
{
    std::string image_path =
        std::string(DATA_DIR) +
        "/DIP3E_Original_Images_CH04/Fig0441(a)(characters_test_pattern).tif";
    Mat src = imread(image_path, 0);

    auto a = IHPFExampel(src, 30);
    auto b = IHPFExampel(src, 60);
    auto c = IHPFExampel(src, 160);

    imshow("src", src);
    imshow("a", a);
    imshow("b", b);
    imshow("c", c);

    waitKey();
    return 0;
}
