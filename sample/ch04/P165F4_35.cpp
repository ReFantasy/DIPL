#include <vector>

#include "ipl.h"
using namespace cv;

using namespace std;

int main(int argc, char *argv[])
{
    std::string image_path =
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0431(d)(blown_ic_crop).tif";
    Mat src = imread(image_path, 0);
    // 寻找最佳图像尺寸
    int optimal_rows = IPL::Nearst2Power(src.rows);
    int optimal_cols = IPL::Nearst2Power(src.cols);
    resize(src, src, {optimal_cols, optimal_rows});

    auto src_vec = IPL::Mat2Vector2D(src);
    IPL::Fourier fourier;
    auto src_fourier = fourier.FFT(src_vec);
    vector<vector<double>> fourier_power(optimal_rows, vector<double>(optimal_cols, 0));
    vector<vector<double>> fourier_angle = fourier_power;
    for (int i = 0; i < optimal_rows; i++)
    {
        for (int j = 0; j < optimal_cols; j++)
        {
            fourier_power[i][j] = abs(src_fourier[i][j]);
            fourier_angle[i][j] = arg(src_fourier[i][j]);
        }
    }

    double scale = 0.5;
    Mat b;
    {
        vector<vector<complex<double>>> fourier_complex(
            optimal_rows, vector<complex<double>>(optimal_cols, {0, 0}));
        // 相角乘以0.5
        for (int i = 0; i < optimal_rows; i++)
        {
            for (int j = 0; j < optimal_cols; j++)
            {
                double angle = fourier_angle[i][j] * scale;
                fourier_complex[i][j] =
                    fourier_power[i][j] * complex<double>{cos(angle), sin(angle)};
            }
        }
        auto b_tmp = fourier.IFFT(fourier_complex);
        Mat _b(optimal_rows, optimal_cols, CV_8UC1);
        for (int i = 0; i < optimal_rows; i++)
        {
            for (int j = 0; j < optimal_cols; j++)
            {
                double v = b_tmp[i][j].real();
                if (v > 255)
                    v = 255;
                if (v < 0)
                    v = 0;
                _b.data[i * optimal_cols + j] = v;
            }
        }
        b = _b;
    }
    Mat c;
    scale = 0.25;
    {
        vector<vector<complex<double>>> fourier_complex(
            optimal_rows, vector<complex<double>>(optimal_cols, {0, 0}));
        // 相角乘以0.5
        for (int i = 0; i < optimal_rows; i++)
        {
            for (int j = 0; j < optimal_cols; j++)
            {
                double angle = fourier_angle[i][j] * scale;
                fourier_complex[i][j] =
                    fourier_power[i][j] * complex<double>{cos(angle), sin(angle)};
            }
        }
        auto b_tmp = fourier.IFFT(fourier_complex);
        Mat _b(optimal_rows, optimal_cols, CV_8UC1);
        for (int i = 0; i < optimal_rows; i++)
        {
            for (int j = 0; j < optimal_cols; j++)
            {
                double v = b_tmp[i][j].real();
                if (v > 255)
                    v = 255;
                if (v < 0)
                    v = 0;
                _b.data[i * optimal_cols + j] = v;
            }
        }
        c = _b;
    }

    imshow("a", src);
    imshow("b", b);
    imshow("c", c);
    waitKey();
    return 0;
}
