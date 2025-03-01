#include <vector>

#include "dipl.h"
using namespace cv;

using namespace std;

int main(int argc, char *argv[])
{
    IPL::Fourier fourier;
    IPL::FourierFilter fourier_filter;

    std::string image_path =
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0431(d)(blown_ic_crop).tif";
    Mat src = imread(image_path, 0);

    // 生成高斯低通滤波核
    Mat src_fft;
    src.copyTo(src_fft);
    int old_rows = src_fft.rows;
    int old_cols = src_fft.cols;
    // 寻找最佳图像尺寸
    int optimal_rows = IPL::Nearst2Power(src_fft.rows);
    int optimal_cols = IPL::Nearst2Power(src_fft.cols);
    resize(src_fft, src_fft, {optimal_cols, optimal_rows});

    // 生成滤波核
    auto a = IPL::GLPF(src_fft.rows, src_fft.cols, 21);
    Mat d = fourier_filter(src_fft, a);

    auto b = IPL::GHPF(src_fft.rows, src_fft.cols, 11);
    Mat e = fourier_filter(src_fft, b);

    auto c = IPL::GLPF(src_fft.rows, src_fft.cols, 11);
    for (auto &e : c)
        for (auto &i : e)
            i = 1 - i * 0.85;

    // auto c = IPL::GHPF(src_fft.rows, src_fft.cols, 10);
    Mat f = fourier_filter(src_fft, c);

    resize(d, d, {old_cols, old_rows});
    resize(e, e, {old_cols, old_rows});
    imshow("d", d);
    imshow("e", e);
    imshow("f", f);

    waitKey();
    return 0;
}
