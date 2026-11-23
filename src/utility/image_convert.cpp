#include "utility/image_convert.h"

std::vector<std::vector<double>> IPL::Mat2Vector2D(const cv::Mat& mat)
{
    if (mat.empty())
        return {};

    // cvtColor 只支持 8U/16U/32F，CV_64F 彩色图要先降到 32F
    cv::Mat src = mat;
    if (src.channels() > 1 && src.depth() == CV_64F)
    {
        cv::Mat tmp;
        src.convertTo(tmp, CV_MAKETYPE(CV_32F, src.channels()));
        src = tmp;
    }

    cv::Mat gray;
    switch (src.channels())
    {
        case 1:
            gray = src; // 已是灰度，直接复用头部
            break;
        case 3:
            cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
            break;
        case 4:
            cv::cvtColor(src, gray, cv::COLOR_BGRA2GRAY); // 丢弃 alpha
            break;
        default:
            CV_Error(cv::Error::StsBadArg, "Mat2Vector2D: unsupported channel count");
    }

    cv::Mat plane;
    gray.convertTo(plane, CV_64F);

    const int rows = plane.rows;
    const int cols = plane.cols;

    std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));
    for (int i = 0; i < rows; i++)
    {
        const double* row = plane.ptr<double>(i);
        std::copy(row, row + cols, dst[i].begin());
    }
    return dst;
}

cv::Mat IPL::Vector2D2Mat(std::vector<std::vector<double>> src)
{
    int rows = src.size();
    int cols = src[0].size();

    cv::Mat dst(rows, cols, CV_8UC1);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            dst.data[i * cols + j] = src[i][j];
        }
    }
    return dst;
}
std::vector<std::vector<double>> IPL::Mat2CentreVector2D(const cv::Mat& mat)
{
    auto dst = std::vector<std::vector<double>>(mat.rows, std::vector<double>(mat.cols, 0));

    int rows = mat.rows;
    int cols = mat.cols;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            dst[i][j] = mat.data[i * cols + j] * pow(-1, i + j);
        }
    }
    return dst;
}

cv::Mat IPL::Complex2Mat(std::vector<std::vector<std::complex<double>>>& src)
{
    int rows = src.size();
    int cols = src[0].size();

    cv::Mat dst(rows, cols, CV_8UC1);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double tmp = std::abs(src[i][j]);
            if (tmp > 255)
                tmp = 255;
            if (tmp < 0)
                tmp = 0;
            dst.data[i * cols + j] = tmp;
        }
    }

    return dst;
}
