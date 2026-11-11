#include "dipl.h"
#include "utility/reflection.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

int GetTerminalWidth(int fallback = 80)
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

void PrintRegisteredFunctions()
{
    int   n    = GetTerminalWidth() / 25;

    auto& reg  = FunctionRegistry::instance();
    auto  list = reg.list();
    std::cout << "Registered functions:\n";
   /* for (const auto& name : list)
        printf("%-25s", name.c_str());*/
    for (int i = 0; i < list.size();i++)
    {
        printf("%-25s", list[i].c_str());
        if ((i + 1) % n == 0)
            printf("\n");
    }
}

int main()
{
    while (true)
    {
// clear the console screen (platform-dependent)
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        PrintRegisteredFunctions();
        std::string input;
        std::cout << "\nEnter sample name to invoke (or 'exit' to quit): ";
        std::getline(std::cin, input);

        if (input == "exit")
            break;

        try
        {
            FunctionRegistry::instance().invoke(input);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}
