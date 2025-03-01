#include <iostream>
#include <vector>

#include "ipl.h"
using namespace cv;

using namespace std;

int main(int argc, char *argv[])
{
    // 妇女原图
    std::string image_path =
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH04/Fig0429(a)(blown_ic).tif";
    Mat src = imread(image_path, 0);

    int rows = src.rows;
    int cols = src.cols;
    IPL::Fourier fourier;

    auto a = IPL::Mat2CentreVector2D(src);

    cout << "please wait ..." << endl;

    // 傅里叶变换
    auto src_fourier = fourier.DFT(a);
    // 直流项置零
    src_fourier[rows / 2][cols / 2] = {0, 0};
    // 傅里叶逆变换
    auto src_idft = fourier.IDFT(src_fourier);

    vector<vector<double>> spectrum(rows, vector<double>(cols, 0));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            int tmp = src_idft[i][j].real() * pow(-1, i + j);
            if (tmp < 0)
                tmp = 0;
            if (tmp > 255)
                tmp = 255;
            spectrum[i][j] = tmp;
        }

    Mat b(rows, cols, CV_8UC1);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            b.data[i * cols + j] = spectrum[i][j];
        }

    imshow("a", src);
    imshow("b", b);

    waitKey();
    return 0;
}
