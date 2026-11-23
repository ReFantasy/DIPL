#include "algorithm/fourier.h"
#include "catch_amalgamated.hpp"
#include "dipl.h"
#include "utility/Timer.h"
#include "utility/common.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

TEST_CASE("parallel for", "[parallel]")
{
    Timer timer;

    // std::vector<double> input = {1, 2, 4, 4};
    //
    // int N = input.size();
    // int M = N;
    //
    // std::cout << "source data:" << std::endl;
    // for (auto e : input)
    // {
    //     std::cout << e << std::endl;
    // }
    // std::cout << std::endl << "DFT:" << std::endl;
    // timer.ReSet();
    // timer.Start();
    // auto out = IPL::Fourier::DFT(input, M);
    // auto t1  = timer.Elapse();
    // for (auto e : out)
    // {
    //     std::cout << e << std::endl;
    // }
    //
    // std::cout << "\nFFT" << std::endl;
    // timer.ReSet();
    // timer.Start();
    // auto fft_res = IPL::Fourier::FFT(input);
    // auto t2      = timer.Elapse();
    // for (auto e : fft_res)
    // {
    //     std::cout << e << std::endl;
    // }
    // std::cout << "T1: " << t1 << " T2 " << t2 << std::endl;
    //
    // auto inv_fft = IPL::Fourier::IFFT(fft_res);
    // for (auto e : inv_fft)
    // {
    //     std::cout << e << std::endl;
    // }

    std::string img_name = std::string(DATA_DIR) + "/DIP3E_Original_Images_CH05/Fig0504(a)(gaussian-noise).tif";
    cv::Mat     src      = cv::imread(img_name, 0);
    std::cout << "image size: " << src.rows << "  " << src.cols << std::endl;
    std::vector<std::vector<double>> img(src.rows, std::vector<double>(src.cols));
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            img[i][j] = src.at<uint>(i, j);
        }
    }

    auto   fft2d     = IPL::Fourier::FFT(img);
    auto   inv_fft2d = Complex2Real(IPL::Fourier::IFFT(fft2d));
    double sum       = 0;
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            sum += std::abs(inv_fft2d[i][j] - img[i][j]);
        }
    }
    std::cout << "fft2d " << sum << std::endl;

    timer.ReSet();
    timer.Start();
    auto dft_2d = IPL::Fourier::DFT(img);
    auto t1     = timer.Elapse();

    timer.ReSet();
    timer.Start();
    auto e2 = IPL::Fourier::FFT(img);
    auto t2 = timer.Elapse();
    std::cout << "t1: " << t1 << "    t2: " << t2 << std::endl;

    sum = 0;
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            sum += std::abs(dft_2d[i][j] - fft2d[i][j]);
        }
    }
    std::cout << "fft and dft error:" << sum << std::endl;

    auto inv_dft2d = Complex2Real(IPL::Fourier::IDFT(dft_2d));
    sum            = 0;
    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            sum += std::abs(inv_dft2d[i][j] - inv_fft2d[i][j]);
        }
    }
    std::cout << "inv_fft and inv_dft error:" << sum << std::endl;
}

TEST_CASE("IsPowerOfTwo", "[Fourier]")
{
    REQUIRE_FALSE(IPL::IsPowerOfTwo(0));
    REQUIRE_FALSE(IPL::IsPowerOfTwo(1));
    REQUIRE_FALSE(IPL::IsPowerOfTwo(-4));
    REQUIRE_FALSE(IPL::IsPowerOfTwo(3));
    REQUIRE_FALSE(IPL::IsPowerOfTwo(6));
    REQUIRE_FALSE(IPL::IsPowerOfTwo(std::numeric_limits<int>::max()));

    for (int k = 1; k <= 30; ++k)
    {
        const int n = 1 << k; // 1..30 位，最高 2^30，不会溢出
        INFO("k = " << k);
        REQUIRE(IPL::IsPowerOfTwo(n));
        if (k < 30)
        {
            const int odd = n + 1;
            INFO("n = " << n);
            REQUIRE_FALSE(IPL::IsPowerOfTwo(odd));
            REQUIRE_FALSE(IPL::IsPowerOfTwo(n + n / 2)); // 3·2^(k-1)，同样必然不是 2 的幂
        }
    }

    REQUIRE(IPL::NearestPowerOfTwo(33) == 32);
    REQUIRE(IPL::NearestPowerOfTwo(47) == 32);
    REQUIRE(IPL::NearestPowerOfTwo(49) == 64);
}
