#include "algorithm/fourier.h"
#include "dipl.h"
#include "utility/common.h"
#include <opencv2/core/hal/interface.h>
// #include <opencv2/highgui.hpp>
// #include "utility/reflection.h"

int P161F4_30()
{
    std::string image_path = std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0429(a)(blown_ic).tif";
    auto        src        = cv::imread(image_path, 0);
    // cv::imshow("a", src);

    auto data     = IPL::MatToPreCenteredVector2D(src);
    auto fft_data = IPL::Fourier::DFT(data);

    int rows = src.rows;
    int cols = src.cols;
    fft_data[src.rows / 2][src.cols / 2] *= 0.0; //= {0,0};
    auto src_idft = IPL::Fourier::IDFT(fft_data);
    auto spectrum = IPL::FreqOffset(IPL::Complex2Real(src_idft, IPL::ComplexComponent::Real));
    cv::imshow("Fig 4.30", IPL::CreateMatU8ByVector2D(spectrum, false));

    cv::waitKey();
}

REGISTER_FUNC("P161F4_30", P161F4_30);
