#include "dipl.h"

void PrintRegisteredFunctions()
{
    int n = GetTerminalWidth() / 25;

    auto& reg  = FunctionRegistry::instance();
    auto  list = reg.list();
    std::cout << "Registered functions:\n";

    for (int i = 0; i < list.size(); i++)
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
