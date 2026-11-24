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
    Mat         src        = imread(image_path, cv::IMREAD_ANYDEPTH | cv::IMREAD_GRAYSCALE);

    IPL::PrintMatInfo(src);
    imshow("a", src);

    int rows = src.rows;
    int cols = src.cols;

    auto img_data = IPL::MatToVector2D(src);

    auto    freq_data = IPL::Fourier::FFT(img_data);
    auto    freq_mag  = IPL::Complex2Real(freq_data, IPL::ComplexComponent::Magnitude);
    cv::Mat freq_img  = IPL::ShowVector2D(freq_mag);
    imshow("b", freq_img);

    auto src_centered = IPL::MatToPreCenteredVector2D(src);
    freq_data         = IPL::Fourier::FFT(src_centered);
    freq_mag          = IPL::Complex2Real(freq_data, IPL::ComplexComponent::Magnitude);
    freq_img          = IPL::ShowVector2D(freq_mag);
    imshow("c", freq_img);

    freq_mag = IPL::Complex2Real(freq_data, IPL::ComplexComponent::LogMagnitude);
    freq_img = IPL::ShowVector2D(freq_mag);
    imshow("d", freq_img);

    // Mat d(rows, cols, CV_8UC1);
    // for (int i = 0; i < rows; i++)
    //     for (int j = 1; j < cols; j++)
    //     {
    //         double tmp           = freq_mag[i][j]*10; // log(1 + abs(fres_centre[i][j]));
    //         d.data[i * cols + j] = tmp;
    //     }
    // imshow("d", d);

    // img        = IPL::MatToVector2D(src);
    // img_centre = IPL::MatToPreCenteredVector2D(src);

    // auto fres        = IPL::Fourier::FFT(img);
    // auto fres_centre = IPL::Fourier::FFT(img_centre);

    // Mat b(rows, cols, CV_64FC1);
    // for (int i = 0; i < rows; i++)
    //     for (int j = 1; j < cols; j++)
    //     {
    //         double tmp         = abs(fres[i][j]);
    //         b.at<double>(i, j) = tmp;
    //     }
    // normalize(b, b, 0, 1, NORM_MINMAX);

    // Mat c(rows, cols, CV_64FC1);
    // for (int i = 0; i < rows; i++)
    //     for (int j = 1; j < cols; j++)
    //     {
    //         double tmp         = abs(fres_centre[i][j]);
    //         c.at<double>(i, j) = tmp;
    //     }
    // normalize(c, c, 0, 1, NORM_MINMAX);

    // Mat d(rows, cols, CV_8UC1);
    // for (int i = 0; i < rows; i++)
    //     for (int j = 1; j < cols; j++)
    //     {
    //         double tmp           = std::log1p(abs(fres_centre[i][j])); // log(1 + abs(fres_centre[i][j]));
    //         d.data[i * cols + j] = tmp;
    //     }

    // imshow("b", b);
    // imshow("c", c);
    // imshow("d", d);

    waitKey();
    return 0;
}
REGISTER_FUNC("P155F4_24", P155F4_24);
