#include "dipl.h"
#include "utility/reflection.h"

int main()
{
    auto& reg = FunctionRegistry::instance();
    // reg.invoke("test2");

    // 调用 int add(int, int)
    // std::any r1 = reg.invoke("add", {1, 2});
    // std::cout << "add(1,2) = " << std::any_cast<int>(r1) << "\n";

    // cv::Mat gray = cv::imread("/Users/refantasy/Downloads/1.jpg", 0);
    // cv::Mat gray   = cv::imread(std::string(DATA_DIR) + "/DIP3E_Original_Images_CH03/Fig0316(4)(bottom_left).tif",0);

    // auto hist = ComputeHistogram(gray);
    // auto img = DrawHistogram(hist);
    // cv::imshow("img", img);
    // cv::waitKey();

    // ShowHistogram(gray, 0);

    auto list = reg.list();
    std::cout << "Registered functions:\n";
    for (const auto& name : list)
        std::cout << "  " << name << "\n";

    reg.invoke("P77F3_20");
}
