#include "dipl.h"
#include "utility/reflection.h"

using namespace cv;
using namespace std;

int P204F5_07()
{
    Mat  a = imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0507(a)(ckt-board-orig).tif", 0);
    Mat  b = imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0507(b)(ckt-board-gauss-var-400).tif", 0);
    auto c = IPL::BlurArithmetic(b, 3);
    auto d = IPL::BlurGeometry(b, 3);

    imshow("a", a);
    imshow("b", b);
    imshow("c", c);
    imshow("d", d);

    waitKey();
    return 0;
}
REGISTER_FUNC("P204F5_07", P204F5_07);
