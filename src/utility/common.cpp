#include "utility/common.h"
#include <cassert>
#include <opencv2/core/hal/interface.h>
#include <opencv2/imgproc.hpp>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif
#include <cmath>
#include <iostream>

namespace IPL
{

    int GetTerminalWidth(int fallback)
    {
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        // 获取标准输出句柄
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hConsole, &csbi))
        {
            // 用可见窗口宽度，而不是缓冲区总宽度
            return csbi.srWindow.Right - csbi.srWindow.Left + 1;
        }
#else
        struct winsize ws;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0)
        {
            return ws.ws_col;
        }
#endif
        return fallback;
    }

    void PrintMatInfo(cv::Mat mat)
    {
        std::cout << "Image rows:" << mat.rows << "  cols:" << mat.cols << "  channels:" << mat.channels() << std::endl;
    }
    std::vector<std::vector<double>> FreqOffset(const std::vector<std::vector<double>>& data)
    {
        auto dst = data;
        for (std::size_t i = 0; i < dst.size(); ++i)
        {
            for (std::size_t j = 0; j < dst[i].size(); ++j)
            {
                if ((i + j) & 1) // (-1)^(i+j)：奇数行为 -1
                    dst[i][j] = -dst[i][j];
            }
        }
        return dst;
    }

    std::vector<std::complex<double>> Real2Complex(const std::vector<double>& vec)
    {
        std::vector<std::complex<double>> res;
        res.reserve(vec.size());

        for (double v : vec)
        {
            res.emplace_back(v, 0.0);
        }
        return res;
    }

    std::vector<std::vector<std::complex<double>>> Real2Complex(const std::vector<std::vector<double>>& vec)
    {
        std::vector<std::vector<std::complex<double>>> res;
        res.reserve(vec.size());

        for (const auto& row : vec)
        {
            res.push_back(Real2Complex(row));
        }
        return res;
    }

    std::vector<double> Complex2RealByComponent(const std::vector<std::complex<double>>& src, ComplexComponent comp)
    {
        // switch 在循环外：每个分支各自实例化模板版本，循环体内没有分支和间接调用
        switch (comp)
        {
            case ComplexComponent::Real:
                return MapVector(src, [](const std::complex<double>& z) { return z.real(); });
            case ComplexComponent::Imag:
                return MapVector(src, [](const std::complex<double>& z) { return z.imag(); });
            case ComplexComponent::Magnitude: // √(re² + im²)
                return MapVector(src, [](const std::complex<double>& z) { return std::abs(z); });
            case ComplexComponent::SquaredMagnitude: // |z|² = re² + im²
                return MapVector(src, [](const std::complex<double>& z) { return std::norm(z); });
            case ComplexComponent::Phase:
                return MapVector(src, [](const std::complex<double>& z) { return std::arg(z); });
            case ComplexComponent::LogMagnitude:
                return MapVector(src, [](const std::complex<double>& z) {
                    // return std::log1p(std::abs(z));
                    return log(1.0 + std::abs(z));
                });
        }
        return {}; // 枚举值非法时返回空向量（编译器的 -Wswitch 仍会提示遗漏的枚举项）
    }

    std::vector<double> Complex2Real(const std::vector<std::complex<double>>& src, ComplexComponent comp)
    {
        return Complex2RealByComponent(src, comp);
    }

    std::vector<std::vector<double>> Complex2Real(const std::vector<std::vector<std::complex<double>>>& src,
                                                  ComplexComponent                                      comp)
    {
        std::vector<std::vector<double>> dst;
        dst.reserve(src.size());
        for (const auto& row : src)
            dst.push_back(Complex2Real(row, comp));
        return dst;
    }

    std::vector<std::vector<double>> MatToVector2D(const cv::Mat& single_img)
    {

        if (single_img.empty() || (single_img.channels() != 1))
            return {};

        cv::Mat float64_img;

        // 转换为 64 位浮点型，通道数保持不变（依然是单通道）
        single_img.convertTo(float64_img, CV_64F);

        const int rows = float64_img.rows;
        const int cols = float64_img.cols;

        std::vector<std::vector<double>> dst(rows, std::vector<double>(cols, 0.0));
        for (int i = 0; i < rows; i++)
        {
            const double* row = float64_img.ptr<double>(i);
            std::copy(row, row + cols, dst[i].begin());
        }
        return dst;
    }

    cv::Mat Vector2DToMat(const std::vector<std::vector<double>>& src)
    {
        if (src.empty())
            return {};

        const auto rows = static_cast<int>(src.size());
        const auto cols = static_cast<int>(src[0].size());

        cv::Mat buf(rows, cols, CV_64FC1);
        for (int i = 0; i < rows; ++i)
        {
            CV_Assert(src[i].size() == static_cast<std::size_t>(cols));
            std::copy(src[i].begin(), src[i].end(), buf.ptr<double>(i));
        }
        return buf;
    }

    std::vector<std::vector<double>> MatToPreCenteredVector2D(const cv::Mat& mat)
    {
        auto dst = MatToVector2D(mat); // 已统一成 CV_64F 灰度，深度/通道无关

        // for (std::size_t i = 0; i < dst.size(); ++i)
        // {
        //     for (std::size_t j = 0; j < dst[i].size(); ++j)
        //     {
        //         if ((i + j) & 1) // (-1)^(i+j)：奇数行为 -1
        //             dst[i][j] = -dst[i][j];
        //     }
        // }
        dst = FreqOffset(dst);
        return dst;
    }

    cv::Mat CreateMatU8ByVector2D(const std::vector<std::vector<double>>& src, bool normalize)
    {

        cv::Mat img = Vector2DToMat(src);
        if (normalize)
        {
            cv::normalize(img, img, 0, 1, cv::NORM_MINMAX);
            img *= 255.0;
        }

        int rows = img.rows;
        int cols = img.cols;

        cv::Mat res(img.rows, img.cols, CV_8UC1);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                res.at<uchar>(i, j) = (uchar)img.at<double>(i, j);
            }
        }
        return res;
    }
} // namespace IPL
