#include "dipl.h"
#include "utility/reflection.h"

using namespace cv;
using namespace std;

int P413F9_14()
{
    Mat src = imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH09/Fig0914(a)(licoln from penny).tif", 0);
    imshow("a", src);

    Mat se = getStructuringElement(cv::MORPH_RECT, {3, 3});
    cout << se << endl;

    Mat src_ero;
    cv::erode(src, src_ero, se);

    Mat b = src - src_ero;
    imshow("b", b);

    waitKey();
    return 0;
}
REGISTER_FUNC("P413F9_14", P413F9_14);
