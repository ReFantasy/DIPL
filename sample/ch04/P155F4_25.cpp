#include "dipl.h"
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    std::string image_path =
        std::string(DATA_DIR) +
        "/DIP3E_Original_Images_CH04/Fig0425(a)(translated_rectangle).tif";
    Mat src_a = imread(image_path, 0);

    int rows_a = src_a.rows;
    int cols_a = src_a.cols;
    IPL::Fourier fourier;

    auto a = vector<vector<double>>(rows_a, vector<double>(cols_a, 0));
    auto c = vector<vector<double>>(rows_a, vector<double>(cols_a, 0));

    c = IPL::Mat2CentreVector2D(src_a);

    auto fres_centre = IPL::Fourier::FFT(c);

    Mat d(rows_a, cols_a, CV_8UC1);
    for (int i = 0; i < rows_a; i++)
        for (int j = 1; j < cols_a; j++)
        {
            double tmp = log(1 + abs(fres_centre[i][j]));
            d.data[i * cols_a + j] = tmp;
        }

    imshow("a", src_a);

    imshow("d", d);

    waitKey();
    return 0;
}
