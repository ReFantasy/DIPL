#include "dipl.h"
#include "utility/reflection.h"

using namespace cv;
using namespace std;

int P205F5_08()
{
    Mat a =
        imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0508(a)(circuit-board-pepper-prob-pt1).tif", 0);
    Mat b =
        imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0508(b)(circuit-board-salt-prob-pt1).tif", 0);
    auto c = IPL::BlurInverseHarmonic(a, 3, 1.5);
    auto d = IPL::BlurInverseHarmonic(b, 3, -1.5);

    imshow("a", a);
    imshow("b", b);
    imshow("c", c);
    imshow("d", d);

    waitKey();
    return 0;
}
REGISTER_FUNC("P205F5_08", P205F5_08);
