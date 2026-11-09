#include "dipl.h"
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    std::string a =
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0504(a)(gaussian-noise).tif";
    Mat d = imread(a, 0);

    d = DrawHistogram(ComputeHistogram(d));
    imshow("高斯", d);

    auto b =
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0504(b)(rayleigh-noise).tif";
    Mat e = imread(b, 0);
    e = DrawHistogram(ComputeHistogram(e));
    imshow("瑞利", e);

    auto c = std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0504(c)(gamma-noise).tif";
    Mat f = imread(c, 0);
    f = DrawHistogram(ComputeHistogram(f));
    imshow("伽马", f);

    auto g =
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0504(g)(neg-exp-noise).tif";
    Mat j = imread(g, 0);
    j = DrawHistogram(ComputeHistogram(j));
    imshow("指数", j);

    auto h =
        std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0504(h)(uniform-noise).tif";
    Mat k = imread(h, 0);
    k = DrawHistogram(ComputeHistogram(k));
    imshow("均匀", k);

    auto i = std::string(DATA_DIR) +
             "/DIP3E_Original_Images_CH05/Fig0504(i)(salt-pepper-noise).tif";
    Mat l = imread(i, 0);
    l = DrawHistogram(ComputeHistogram(l));
    imshow("椒盐", l);

    waitKey();
    return 0;
}
