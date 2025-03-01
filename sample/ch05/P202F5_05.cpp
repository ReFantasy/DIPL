#include "ipl.h"
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat s = imread(std::string(DATA_DIR) +
                       "/DIP3E_Original_Images_CH05/Fig0505(a)(applo17_boulder_noisy).tif",
                   0);

    auto src = IPL::Mat2CentreVector2D(s);
    auto src_fourier = IPL::Fourier::DFT(src);

    int rows = s.rows;
    int cols = s.cols;

    cv::Mat dst(rows, cols, CV_64FC1);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {

            dst.at<double>(i, j) = std::abs(src_fourier[i][j]);
        }
    }
    normalize(dst, dst, 0, 1, NORM_MINMAX);
    imshow("a", s);
    imshow("b", dst);

    waitKey();
    return 0;
}
