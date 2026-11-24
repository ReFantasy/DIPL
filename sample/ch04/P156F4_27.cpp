#include "algorithm/fourier.h"
#include "dipl.h"
#include "utility/common.h"
#include "utility/reflection.h"
#include <cassert>
#include <complex>
#include <opencv2/imgproc.hpp>
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

    auto src_fourier_2 = fourier.FFT(IPL::MatToVector2D(src)); // DC 在左上角
    auto mag           = IPL::Complex2Real(src_fourier_2, IPL::ComplexComponent::Magnitude);
    auto shifted =
        IPL::FreqOffset(mag); // 让 (0,0) 原点落在画面中央                                      // 频谱乘 (-1)^(u+v)
    auto _d = IPL::Complex2Real(fourier.IFFT(IPL::Real2Complex(shifted)), IPL::ComplexComponent::Real);
    auto d  = IPL::CreateMatU8ByVector2D(_d); // 亮斑落在中心

    // 矩形谱和妇女的相位角
    image_path  = std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0424(a)(rectangle).tif";
    Mat fig4_24 = imread(image_path, 0);
    cv::resize(fig4_24, fig4_24, src.size());

    auto spec_rect =
        IPL::Complex2Real(IPL::Fourier::FFT(IPL::MatToVector2D(fig4_24)), IPL::ComplexComponent::Magnitude);

    auto women_phase = IPL::Complex2Real(IPL::Fourier::FFT(IPL::MatToVector2D(src)), IPL::ComplexComponent::Phase);
    IPL::PrintMatInfo(src);
    IPL::PrintMatInfo(fig4_24);
    std::vector<std::vector<std::complex<double>>> freq(spec_rect.size(),
                                                        std::vector<std::complex<double>>(spec_rect[0].size()));
    for (int i = 0; i < spec_rect.size(); i++)
    {
        for (int j = 0; j < spec_rect[0].size(); j++)
        {
            freq[i][j] = spec_rect[i][j] * IPL::EulerTransform(women_phase[i][j]).NativeComplex();
        }
    }
    auto _e = IPL::Complex2Real(fourier.IFFT(freq), IPL::ComplexComponent::Real);
    auto e  = IPL::CreateMatU8ByVector2D(_e);

    // 矩形的相角妇女的谱
    auto spec_phase = IPL::Complex2Real(IPL::Fourier::FFT(IPL::MatToVector2D(fig4_24)), IPL::ComplexComponent::Phase);

    auto women_spec = IPL::Complex2Real(IPL::Fourier::FFT(IPL::MatToVector2D(src)), IPL::ComplexComponent::Magnitude);

    freq = std::vector<std::vector<std::complex<double>>>(spec_phase.size(),
                                                          std::vector<std::complex<double>>(spec_phase[0].size()));
    for (int i = 0; i < spec_phase.size(); i++)
    {
        for (int j = 0; j < spec_phase[0].size(); j++)
        {
            freq[i][j] = women_spec[i][j] * IPL::EulerTransform(spec_phase[i][j]).NativeComplex();
        }
    }
    auto _f = IPL::Complex2Real(fourier.IFFT(freq), IPL::ComplexComponent::Real);
    auto f  = IPL::CreateMatU8ByVector2D(_f);

    int OFFSET = 512;
    imshow("a", src);
    imshow("b", b);
    imshow("c", c);
    imshow("d", d);
    imshow("e", e);
    imshow("f", f);
    cv::moveWindow("a", OFFSET * 0, 0);
    cv::moveWindow("b", OFFSET * 1, 0);
    cv::moveWindow("c", OFFSET * 2, 0);
    cv::moveWindow("d", OFFSET * 0, OFFSET);
    cv::moveWindow("e", OFFSET * 1, OFFSET);
    cv::moveWindow("f", OFFSET * 2, OFFSET);

    waitKey();
    return 0;
}
REGISTER_FUNC("P156F4_27", P156F4_27);
