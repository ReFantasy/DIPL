#include <vector>

#include "dipl.h"
using namespace cv;

using namespace std;

int main(int argc, char *argv[])
{
    IPL::Fourier fourier;
    IPL::FourierFilter fourier_filter;

    std::string image_path =
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0432(a)(square_original).tif";
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
    auto kernel = IPL::GLPF(src_fft.rows, src_fft.cols, 21);
    Mat b = fourier_filter(src_fft, kernel);
    resize(b, b, {old_cols, old_rows});

    // 填充图像
    Mat src_multi(src.rows * 2, src.cols * 2, CV_8UC1, cv::Scalar(0));
    for (int i = 0; i < src.rows; i++)
        for (int j = 0; j < src.cols; j++)
        {
            src_multi.data[i * src.cols * 2 + j] = src.data[i * src.cols + j];
        }
    old_rows = src_multi.rows;
    old_cols = src_multi.cols;
    optimal_rows = IPL::Nearst2Power(src_multi.rows);
    optimal_cols = IPL::Nearst2Power(src_multi.cols);
    resize(src_multi, src_multi, {optimal_cols, optimal_rows});
    kernel = IPL::GLPF(src_multi.rows, src_multi.cols, 21);
    Mat c = fourier_filter(src_multi, kernel);
    resize(c, c, {old_cols, old_rows});
    c = c(Range(0, src.rows), Range(0, src.cols));

    imshow("a", src);
    imshow("b", b);
    imshow("c", c);
    waitKey();
    return 0;
}
