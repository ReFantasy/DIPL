#include "dipl.h"
#include "utility/common.h"
#include "utility/reflection.h"
#include <complex>
#include <vector>
using namespace cv;
using namespace std;

int P156F4_27()
{
    // 妇女原图
    std::string image_path = std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0427(a)(woman).tif";
    Mat         src        = imread(image_path, 0);

    int          rows = src.rows;
    int          cols = src.cols;
    IPL::Fourier fourier;

    auto a           = IPL::MatToPreCenteredVector2D(src); // IPL::MatToVector2D(src);
    auto src_fourier = fourier.FFT(a);

    // 获取相角
    vector<vector<double>> angle = IPL::Complex2Real(src_fourier, IPL::ComplexComponent::Phase);
    cv::Mat                b     = IPL::CreateMatU8ByVector2D(angle);

    // 仅使用相角重建
    auto angle_build =
        IPL::MapVector(angle, [](const double& ang) { return std::complex<double> {cos(ang), sin(ang)}; });
    auto _c = IPL::Complex2Real(fourier.IFFT(angle_build), IPL::ComplexComponent::Real);
    auto c  = IPL::CreateMatU8ByVector2D(IPL::FreqOffset(_c));

    // 仅使用谱重建
    vector<vector<complex<double>>> spectrum(rows, vector<complex<double>>(cols, {0, 0}));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            spectrum[i][j] = {abs(src_fourier[i][j]), 0};
        }
    auto _d = fourier.IFFT(spectrum);
    Mat  d(rows, cols, CV_64FC1);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            d.at<double>(i, j) = abs(_d[i][j]);
        }
    normalize(d, d, 0, 1, NORM_MINMAX);

    // fig 4.24谱和妇女的相位角
    image_path = std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0424(a)(rectangle).tif";
    Mat                             fig4_24  = imread(image_path, 0);
    auto                            _fig4_24 = IPL::MatToVector2D(fig4_24);
    vector<vector<complex<double>>> _e(rows, vector<complex<double>>(cols, {0, 0}));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            _e[i][j] = {abs(_fig4_24[i][j]) * cos(angle[i][j]), abs(_fig4_24[i][j]) * sin(angle[i][j])};
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
    auto                            _fig4_24_fourier = fourier.FFT(_fig4_24);
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
REGISTER_FUNC("P156F4_27", P156F4_27);
