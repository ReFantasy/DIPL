#include "dipl.h"
#include "utility/reflection.h"

using namespace cv;
using namespace std;
int P410F9_11()
{
    Mat src = imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH09/Fig0911(a)(noisy_fingerprint).tif", 0);
    imshow("a", src);

    Mat se = getStructuringElement(cv::MORPH_RECT, {3, 3});
    cout << se << endl;

    Mat c;
    cv::erode(src, c, se);
    imshow("c", c);

    Mat d;
    cv::dilate(c, d, se);
    imshow("d", d);

    Mat e;
    cv::dilate(d, e, se);
    imshow("e", e);

    Mat f;
    cv::erode(e, f, se);
    imshow("f", f);

    waitKey();
    return 0;
}

REGISTER_FUNC("P410F9_11", P410F9_11);
