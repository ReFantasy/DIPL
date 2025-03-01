#include <iostream>
#include <vector>

#include "dipl.h"
using namespace cv;

using namespace std;
using namespace cv;

template <typename T>
void Print(const vector<vector<T>> &vt)
{
    for (const auto &e : vt)
    {
        for (const auto &i : e)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}
std::ostream &operator<<(std::ostream &os, const std::complex<double> &cd)
{
    os << "[" << cd.real() << "," << cd.imag() << "]";
    return os;
}

// 傅里叶滤波示例
void FourierFilterExampel(const Mat &src);

void OpencvFouier(Mat srcImage);

int main(int argc, char *argv[])
{
    /*Mat a =
    imread("../data/DIP3E_Original_Images_CH05/Fig0508(a)(circuit-board-pepper-prob-pt1).tif",
    0); Mat b =
    imread("../data/DIP3E_Original_Images_CH05/Fig0508(b)(circuit-board-salt-prob-pt1).tif",
    0); auto c = IPL::BlurMiddle(a, 3); auto d = IPL::BlurMiddle(b, 3); imshow("a", a);
    imshow("b", b);
    imshow("c", c);
    imshow("d", d);*/

    // cv::pyrUp(a, a);

    Mat src = imread(std::string(DATA_DIR) +
                         "/DIP3E_Original_Images_CH09/Fig0905(a)(wirebond-mask).tif",
                     0);
    Mat se = getStructuringElement(cv::MORPH_RECT, {11, 11});

    Mat res;
    cv::erode(src, res, se);

    imshow("src", src);
    imshow("res", res);

    waitKey();
    return 0;
}

void FourierFilterExampel(const Mat &src)
{
    assert(src.type() == CV_8UC1);

    // 初始化变量和数据
    Timer timer;
    Rand<double> _rand(1, 10);
    IPL::FourierFilter fourier_filter;

    // ------------------------------------- FFT ---------------------------------------
    cout << "fft" << endl;
    Mat src_fft;
    src.copyTo(src_fft);
    int old_rows = src_fft.rows;
    int old_cols = src_fft.cols;
    // 寻找最佳图像尺寸
    int optimal_rows = IPL::Nearst2Power(src_fft.rows);
    int optimal_cols = IPL::Nearst2Power(src_fft.cols);
    resize(src_fft, src_fft, {optimal_cols, optimal_rows});

    // 生成滤波核
    auto kernel_fft = IPL::GHPF(src_fft.rows, src_fft.cols, 160);

    timer.Start();
    Mat fft = fourier_filter(src_fft, kernel_fft);
    cout << "fft: " << timer.Elapse() << " milliseconds" << endl;

    resize(fft, fft, {old_cols, old_rows});
    imshow("fft", fft);

    cout << endl;

    // ------------------------------------- DFT ---------------------------------------
    cout << "dft" << endl;
    Mat src_dft;
    src.copyTo(src_dft);
    // 生成滤波核
    auto kernel_dft = IPL::GHPF(src_dft.rows, src_dft.cols, 160);
    timer.ReSet();
    Mat dft = fourier_filter(src_dft, kernel_dft, 1);
    cout << "dft: " << timer.Elapse() << " milliseconds" << endl;
    imshow("dft", dft);
}

void OpencvFouier(Mat srcImage)
{
    // 2.将输入图像延扩到最佳尺寸，边界用0补充
    int m = getOptimalDFTSize(srcImage.rows);
    int n = getOptimalDFTSize(srcImage.cols);
    // 将添加的像素初始化为0。
    Mat padded;
    copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols,
                   BORDER_CONSTANT, Scalar::all(0));

    // 3.为傅里叶变换的结果（实部和虚部）分配空间。
    // 将planes数组组合合并成一个多通道的数组complexI
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);

    // 4.进行离散傅里叶变换
    dft(complexI, complexI);

    // 5.将复数转换为幅值，即 log(1+sqrt(Re(DFT(I))^2 + Im(DFT(I))^2)
    split(complexI, planes); // 将多通道数组complexI分离成几个单通道数组，[0]=Re,[1]=Im
    magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
    Mat magnitudeImage = planes[0];

    // 6.进行对数尺度（logarithmic scale）缩放
    magnitudeImage += Scalar::all(1);
    log(magnitudeImage, magnitudeImage); // 求自然对数

    // 7.剪切和重分布幅度图象限
    // 若有奇数行或奇数列，进行频谱裁剪
    magnitudeImage =
        magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));

    // 重新排列傅里叶图像中的象限，使得原点位于图像中心
    int cx = magnitudeImage.cols / 2;
    int cy = magnitudeImage.rows / 2;
    Mat q0(magnitudeImage, Rect(0, 0, cx, cy));   // ROI区域的左上
    Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));  // ROI区域的右上
    Mat q2(magnitudeImage, Rect(0, cy, cx, cy));  // ROI区域的左下
    Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI区域的右下
    // 交换象限（左上与右下进行交换）
    Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    // 交换象限（右上与左下进行交换）
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    // 8.归一化，用0到1之间的浮点值将矩阵变换为可视化的图像格式
    normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

    // 9.显示效果图
    imshow("OpenCV fourier", magnitudeImage);
}
