#include "dipl.h"
#include "utility/reflection.h"

using namespace cv;
using namespace std;

int P407F9_07()
{
    Mat src = imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH09/Fig0907(a)(text_gaps_1_and_2_pixels).tif", 0);
    imshow("a", src);

    Mat se = getStructuringElement(cv::MORPH_CROSS, {3, 3});
    cout << se << endl;

    Mat c;
    cv::dilate(src, c, se);
    imshow("c", c);

    waitKey();
    return 0;
}
REGISTER_FUNC("P407F9_07", P407F9_07);
