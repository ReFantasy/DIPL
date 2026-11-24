#include "algorithm/fourier.h"
#include "dipl.h"
#include "utility/common.h"
#include "utility/reflection.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

int P155F4_24()
{
    std::string image_path = std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0424(a)(rectangle).tif";
    Mat         src        = imread(image_path, 0);

    IPL::PrintMatInfo(src);
    imshow("a", src);

    int rows = src.rows;
    int cols = src.cols;

    auto img_data = IPL::MatToVector2D(src);

    auto    freq_data = IPL::Fourier::FFT(img_data);
    auto    freq_mag  = IPL::Complex2Real(freq_data, IPL::ComplexComponent::Magnitude);
    cv::Mat freq_img  = IPL::CreateMatU8ByVector2D(freq_mag);
    imshow("b", freq_img);

    auto src_centered = IPL::MatToPreCenteredVector2D(src);
    freq_data         = IPL::Fourier::FFT(src_centered);
    freq_mag          = IPL::Complex2Real(freq_data, IPL::ComplexComponent::Magnitude);
    freq_img          = IPL::CreateMatU8ByVector2D(freq_mag);
    imshow("c", freq_img);

    freq_mag = IPL::Complex2Real(freq_data, IPL::ComplexComponent::LogMagnitude);
    freq_img = IPL::CreateMatU8ByVector2D(freq_mag);
    imshow("d", freq_img);

    waitKey();
    return 0;
}
REGISTER_FUNC("P155F4_24", P155F4_24);
