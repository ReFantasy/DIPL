#include "dipl.h"
#include "utility/reflection.h"

void PrintRegisteredFunctions()
{
    auto& reg  = FunctionRegistry::instance();
    auto  list = reg.list();
    std::cout << "Registered functions:\n";
    for (const auto& name : list)
        printf("%-25s", name.c_str());
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
        std::cout << "\nEnter function name to invoke (or 'exit' to quit): ";
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
