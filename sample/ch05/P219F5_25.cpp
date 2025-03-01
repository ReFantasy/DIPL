#include <vector>

#include "dipl.h"

using namespace cv;
using namespace std;

Mat P219(Mat src, double k)
{

    int rows = src.rows;
    int cols = src.cols;

    auto src_vec = IPL::Mat2Vector2D(src);
    auto src_fourier = IPL::Fourier::FFT(src_vec);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            src_fourier[i][j] *= exp(-k * pow(pow(i, 2) + pow(j, 2), 5 / 6.0));
        }
    }

    auto idft = IPL::Fourier::IFFT(src_fourier);

    Mat dst(rows, cols, CV_8UC1);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int v = std::abs(idft[i][j] * pow(-1, i + j));
            if (v > 255)
                v = 255;
            dst.data[i * cols + j] = v;
        }
    }

    return dst;
}

int main(int argc, char *argv[])
{
    Mat src = imread(std::string(DATA_DIR) +
                         "/DIP3E_Original_Images_CH05/Fig0525(a)(aerial_view_no_turb).tif",
                     0);
    resize(src, src, {512, 512});

    auto b = P219(src, 0.00025);
    auto c = P219(src, 0.00001);
    auto d = P219(src, 0.000025);

    imshow("a", src);
    imshow("b", b);
    imshow("c", c);
    imshow("d", d);

    waitKey();
    return 0;
}

// 陷波滤波器
cv::Mat notch_kernel(cv::Mat &scr, std::vector<cv::Point> &notch_pot, float D0)
{
    cv::Mat notch_pass(scr.size(), CV_32FC2);
    int row_num = scr.rows;
    int col_num = scr.cols;
    int n = 4;

    for (int i = 0; i < row_num; i++)
    {
        float *p = notch_pass.ptr<float>(i);

        for (int j = 0; j < col_num; j++)
        {
            float h_nr = 1.0;
            for (unsigned int k = 0; k < notch_pot.size(); k++)
            {
                int u_k = notch_pot.at(k).y;
                int v_k = notch_pot.at(k).x;
                float dk = sqrt(pow((i - u_k), 2) + pow((j - v_k), 2));
                float d_k = sqrt(pow((i + u_k), 2) + pow((j + v_k), 2));
                float dst_dk = 1.0 / (1.0 + pow(D0 / dk, 2 * n));
                float dst_d_k = 1.0 / (1.0 + pow(D0 / d_k, 2 * n));
                h_nr = dst_dk * dst_d_k * h_nr;
                // std::cout <<  "notch_pot: " << notch_pot.at(k) << std::endl;
            }

            p[2 * j] = h_nr;
            p[2 * j + 1] = h_nr;
        }
    }

    cv::Mat temp[] = {cv::Mat::zeros(scr.size(), CV_32FC1),
                      cv::Mat::zeros(scr.size(), CV_32FC1)};
    cv::split(notch_pass, temp);

    std::string name = "notch滤波器d0=" + std::to_string(D0);
    cv::Mat show;
    cv::normalize(temp[0], show, 1, 0, NORM_MINMAX);
    cv::imshow(name, show);
    return notch_pass;
}
