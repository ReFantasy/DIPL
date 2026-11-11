#include "dipl.h"
using namespace cv;
using namespace std;
#include "utility/reflection.h"

int P292F7_03()
{
    Mat src = imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH07/vase.tif", 0);

    auto src_vec = IPL::Mat2Vector2D(src);

    std::vector<std::vector<double>> approximate;
    std::vector<std::vector<double>> residual;
    IPL::PyramidExample(src_vec, approximate, residual);
    auto a_8 = IPL::NormalizeVec2DToMat(approximate);
    auto b_9 = IPL::NormalizeVec2DToMat(residual);

    auto _approximate = approximate;
    IPL::PyramidExample(_approximate, approximate, residual);
    auto a_7 = IPL::NormalizeVec2DToMat(approximate);
    auto b_8 = IPL::NormalizeVec2DToMat(residual);

    _approximate = approximate;
    IPL::PyramidExample(_approximate, approximate, residual);
    auto a_6 = IPL::NormalizeVec2DToMat(approximate);
    auto b_7 = IPL::NormalizeVec2DToMat(residual);

    _approximate = approximate;
    IPL::PyramidExample(_approximate, approximate, residual);
    auto a_5 = IPL::NormalizeVec2DToMat(approximate);
    auto b_6 = IPL::NormalizeVec2DToMat(residual);

    imshow("a_9", src);
    imshow("b_9", b_9);
    imshow("a_8", a_8);
    imshow("b_8", b_8);
    imshow("a_7", a_7);
    imshow("b_7", b_7);
    imshow("a_6", a_6);
    imshow("b_6", b_6);

    waitKey();
    return 0;
}
REGISTER_FUNC("P292F7_03", P292F7_03);
