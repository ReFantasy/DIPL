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
    auto src_fourier = fourier.DFT(a);

    // 获取相角
    vector<vector<double>> spectrum(rows, vector<double>(cols, 0));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            spectrum[i][j] = log(1 + abs(src_fourier[i][j]));
        }

    Mat b(rows, cols, CV_64FC1);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            b.at<double>(i, j) = spectrum[i][j];
        }
    normalize(b, b, 0, 1, NORM_MINMAX);
    imshow("a", src);
    imshow("b", b);

    waitKey();
    return 0;
}
