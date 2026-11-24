#include "algorithm/fourier.h"
#include "dipl.h"
#include "utility/common.h"
#include "utility/filter.h"
#include "utility/reflection.h"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/version.hpp>

// 判断主版本号是否大于等于 5
#if CV_VERSION_MAJOR >= 5
    #include <opencv2/geometry.hpp>  // OpenCV 5 的路径
#endif
#include <vector>
using namespace cv;
using namespace std;

int P155F4_25()
{
    std::string image_path = std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0425(a)(translated_rectangle).tif";
    Mat         src        = imread(image_path, 0);
    cv::imshow("a", src);
    cv::moveWindow("a", 0, 0);

    int rows = src.rows;
    int cols = src.cols;

    auto img_vec   = IPL::MatToPreCenteredVector2D(src);
    auto freq_data = IPL::Fourier::FFT(img_vec);
    auto freq_mag  = IPL::Complex2Real(freq_data, IPL::ComplexComponent::LogMagnitude);
    auto freq_img  = IPL::CreateMatU8ByVector2D(freq_mag);
    cv::imshow("b", freq_img);
    cv::moveWindow("b", cols, 0);

    image_path = std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0424(a)(rectangle).tif";
    src        = imread(image_path, 0);

    double      angle = 45.0; // 旋转角度（正数表示逆时针旋转）
    double      scale = 1.0;  // 缩放因子（1.0 表示保持原大小）
    cv::Point2f center(src.cols / 2.0, src.rows / 2.0);
    cv::Mat     rot_mat = cv::getRotationMatrix2D(center, angle, scale);
    cv::Mat     rotated_img;
    cv::warpAffine(src, rotated_img, rot_mat, src.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
    cv::imshow("c", rotated_img);
    cv::moveWindow("c", 0, rows);

    cv::Mat rotated_img_fourier = IPL::FourierTransform(rotated_img);
    cv::imshow("d", rotated_img_fourier);
    cv::moveWindow("d", cols, rows);

    waitKey();
    return 0;
}
REGISTER_FUNC("P155F4_25", P155F4_25);
