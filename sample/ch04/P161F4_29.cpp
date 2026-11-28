#include "dipl.h"
// #include <opencv2/highgui.hpp>
// #include "utility/reflection.h"

int P161F4_29()
{
    std::string image_path = std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0429(a)(blown_ic).tif";
    auto        src        = cv::imread(image_path, 0);
    cv::imshow("a", src);

    auto data     = IPL::MatToPreCenteredVector2D(src);
    auto fft_data = IPL::Fourier::DFT(data);
    auto ft_img   = IPL::CreateMatU8ByVector2D(IPL::Complex2Real(fft_data, IPL::ComplexComponent::LogMagnitude));
    cv::imshow("b", ft_img);

    cv::waitKey();
}

REGISTER_FUNC("P161F4_29", P161F4_29);
