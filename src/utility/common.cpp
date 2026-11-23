#include "utility/common.h"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

int GetTerminalWidth(int fallback)
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    // 获取标准输出句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        // 用可见窗口宽度，而不是缓冲区总宽度
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
#else
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0)
    {
        return ws.ws_col;
    }
#endif
    return fallback;
}
std::vector<std::complex<double>> Real2Complex(const std::vector<double>& vec)
{
    int N = vec.size();

    std::vector<std::complex<double>> res(N);
    for (int i = 0; i < N; i++)
    {
        res[i] = {vec[i], 0};
    }
    return res;
}

std::vector<std::vector<std::complex<double>>> Real2Complex(const std::vector<std::vector<double>>& vec)
{
    std::vector<std::vector<std::complex<double>>> res;
    for (int i = 0; i < vec.size(); i++)
    {
        res.push_back(Real2Complex(vec[i]));
    }
    return res;
}

std::vector<double> Complex2Real(const std::vector<std::complex<double>>& complexs)
{
    int N = complexs.size();

    std::vector<double> vec(N);
    for (int i = 0; i < N; i++)
    {
        vec[i] = complexs[i].real();
    }
    return vec;
}
std::vector<std::vector<double>> Complex2Real(const std::vector<std::vector<std::complex<double>>>& complexs)
{
    std::vector<std::vector<double>> res;
    for (int i = 0; i < complexs.size(); i++)
    {
        res.push_back(Complex2Real(complexs[i]));
    }
    return res;
}
