#include "ipl.h"
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat src =
        imread(std::string(DATA_DIR) +
                   "/DIP3E_Original_Images_CH09/Fig0907(a)(text_gaps_1_and_2_pixels).tif",
               0);
    imshow("a", src);

    Mat se = getStructuringElement(cv::MORPH_CROSS, {3, 3});
    cout << se << endl;

    Mat c;
    cv::dilate(src, c, se);
    imshow("c", c);

    waitKey();
    return 0;
}
