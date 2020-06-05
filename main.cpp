#include "token.h"
#include "scanner.h"
#include "parser.h"

int main()
{

    std::ifstream ifs;
    std::string file = "scanner_test";
    ifs.open(file);
    bool bResult = false;

    if (ifs.is_open())
    {
        std::cout << "Input file is " << file << std::endl;
        Scanner sc(&ifs);

        //return 0;

        Parser test(sc);
        bResult = test.Parse();
        if (bResult)
        {
            std::cout << "Correct" << std::endl;
        }
        else
        {
            std::cout << "Incorrect" << std::endl;
        }

        ifs.close();
    }

    return 0;
}