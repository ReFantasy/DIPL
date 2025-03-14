﻿#include "dipl.h"

using namespace cv;
using namespace std;

int main(int argc, char *argv[])

{

    Mat a = imread(std::string(DATA_DIR) +
                       "/DIP3E_Original_Images_CH05/Fig0512(a)(ckt-uniform-var-800).tif",
                   0);

    Mat b = imread(
        std::string(DATA_DIR) +
            "/DIP3E_Original_Images_CH05/Fig0512(b)(ckt-uniform-plus-saltpepr-prob-pt1).tif",
        0);

    auto c = IPL::BlurArithmetic(b, 5);

    auto d = IPL::BlurGeometry(b, 5);

    auto e = IPL::BlurMedian(b, 5);

    auto f = IPL::BlurModifiedAlpha(b, 5, 5);

    imshow("a", a);

    imshow("b", b);

    imshow("c", c);

    imshow("d", d);

    imshow("e", e);

    imshow("f", f);

    waitKey();

    return 0;
}
