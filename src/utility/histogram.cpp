#include "utility/histogram.h"
#include <opencv2/highgui.hpp>
#include <vector>

std::vector<int> ComputeHistogram(const cv::Mat& gray_image)
{
    std::vector<int>     hist(256, 0);
    const unsigned char* pdata = gray_image.data;

    // for (int i=0; i<gray_image.rows*gray_image.cols; i++)
    //     hist[static_cast<int>(pdata[i])]++;

#pragma omp parallel for
    for (int r = 0; r < gray_image.rows; ++r)
    {
        const auto* row = gray_image.ptr<uchar>(r);
        for (int c = 0; c < gray_image.cols; ++c)
#pragma omp atomic
            ++hist[row[c]];
    }

    return hist;
}

cv::Mat DrawHistogram(std::vector<int> hist, cv::Scalar fg, cv::Scalar bg, int n, int rows)
{
    const double max_value = *std::max_element(hist.begin(), hist.end());

    std::vector<double> norm_hist(256, 0);
#pragma omp parallel for
    for (int i = 0; i < 256; ++i)
        norm_hist[i] = hist[i] / max_value;

    int cols = 256 * n;

    cv::Mat img(rows, cols, CV_8UC3, bg);

    for (int i = 0; i < cols; i += n)
    {
        cv::rectangle(img, cv::Rect(i, 0, n, norm_hist[i / n] * rows), fg, cv::FILLED);
    }
    cv::flip(img, img, 0);
    return img;
}
cv::Mat ShowHistogram(const cv::Mat& gray_image, int delay)
{
    auto hist = ComputeHistogram(gray_image);
    auto img  = DrawHistogram(hist);
    cv::imshow("Histogram", img);
    cv::waitKey(delay);
    return img;
}
