#include "dipl.h"
using namespace cv;
using namespace std;

#include "utility/reflection.h"

int P207F5_10()
{
    Mat a =
        imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0510(a)(ckt-board-saltpep-prob.pt05).tif", 0);
    Mat  b = IPL::BlurMedian(a, 3);
    auto c = IPL::BlurMedian(b, 3);
    auto d = IPL::BlurMedian(c, 3);

    imshow("a", a);
    imshow("b", b);
    imshow("c", c);
    imshow("d", d);

    waitKey();
    return 0;
}
REGISTER_FUNC("P207F5_10", P207F5_10);
