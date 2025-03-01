#include <vector>

#include "ipl.h"
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    // 妇女原图
    std::string image_path =
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0427(a)(woman).tif";
    Mat src = imread(image_path, 0);

    int rows = src.rows;
    int cols = src.cols;
    IPL::Fourier fourier;

    auto a = IPL::Mat2Vector2D(src);
    auto src_fourier = fourier.FFT(a);

    // 获取相角
    vector<vector<double>> angle(rows, vector<double>(cols, 0));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            angle[i][j] = arg(src_fourier[i][j]);
        }
    Mat b(rows, cols, CV_8UC1);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            b.data[i * cols + j] = angle[i][j];
        }

    // 仅使用相角重建
    vector<vector<complex<double>>> angle_build(rows, vector<complex<double>>(cols, {0, 0}));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            angle_build[i][j] = {cos(angle[i][j]), sin(angle[i][j])};
        }
    auto _c = fourier.IFFT(angle_build);
    Mat c(rows, cols, CV_64FC1);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            c.at<double>(i, j) = abs(_c[i][j]);
        }
    normalize(c, c, 0, 1, NORM_MINMAX);

    // 仅使用谱重建
    vector<vector<complex<double>>> spectrum(rows, vector<complex<double>>(cols, {0, 0}));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            spectrum[i][j] = {abs(src_fourier[i][j]), 0};
        }
    auto _d = fourier.IFFT(spectrum);
    Mat d(rows, cols, CV_64FC1);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            d.at<double>(i, j) = abs(_d[i][j]);
        }
    normalize(d, d, 0, 1, NORM_MINMAX);

    // fig 4.24谱和妇女的相位角
    image_path =
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0424(a)(rectangle).tif";
    Mat fig4_24 = imread(image_path, 0);
    auto _fig4_24 = IPL::Mat2Vector2D(fig4_24);
    vector<vector<complex<double>>> _e(rows, vector<complex<double>>(cols, {0, 0}));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            _e[i][j] = {abs(_fig4_24[i][j]) * cos(angle[i][j]),
                        abs(_fig4_24[i][j]) * sin(angle[i][j])};
        }
    _e = fourier.IFFT(_e);
    Mat e(rows, cols, CV_64FC1);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            e.at<double>(i, j) = abs(_e[i][j]);
        }
    normalize(e, e, 0, 1, NORM_MINMAX);

    // 矩形的相角妇女的谱
    auto _fig4_24_fourier = fourier.FFT(_fig4_24);
    vector<vector<complex<double>>> _f(rows, vector<complex<double>>(cols, {0, 0}));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            _f[i][j] = {cos(arg(_fig4_24_fourier[i][j])) * abs(src_fourier[i][j]),
                        sin(arg(_fig4_24_fourier[i][j])) * abs(src_fourier[i][j])};
        }
    _f = fourier.IFFT(_f);
    Mat f(rows, cols, CV_64FC1);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            f.at<double>(i, j) = abs(_f[i][j]);
        }
    normalize(f, f, 0, 1, NORM_MINMAX);

    imshow("a", src);
    imshow("b", b);
    imshow("c", c);
    imshow("d", d);
    imshow("e", e);
    imshow("f", f);

    waitKey();
    return 0;
}
