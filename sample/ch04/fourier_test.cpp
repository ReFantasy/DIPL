#include "dipl.h"
#include "fourier.h"
#include <vector>

int main()
{
    Timer timer;
    std::cout << "一维傅立叶变换 例4.4" << std::endl;
    std::vector<double> input = {1, 2, 4, 4};

    std::cout << "source data:" << std::endl;
    for (auto e : input)
    {
        std::cout << e << std::endl;
    }

    std::cout << std::endl << "DFT:" << std::endl;
    timer.Start();
    auto out = IPL::Fourier::DFT(input);
    timer.Suspend();
    for (auto e : out)
    {
        std::cout << e << std::endl;
    }

    std::cout << std::endl << "IDFT:" << std::endl;
    timer.Continue();
    auto src = IPL::Fourier::IDFT(out);

    auto comsume_time = timer.Elapse<std::chrono::microseconds>();

    for (auto e : src)
    {
        std::cout << e << std::endl;
    }
    std::cout << "time:" << comsume_time << " microseconds" << std::endl;
}
