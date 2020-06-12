#include "token.h"
#include "scanner.h"
#include "parser.h"

int main()
{

    std::ifstream fileStream;
    std::string file = "parser_evaluator_test";
    fileStream.open(file);
    bool parseResult = false;

    if (fileStream.is_open())
    {
        std::cout << "Input file is " << file << std::endl;
        Scanner sc(&fileStream);

        Parser parsingTask(sc);
        parseResult = parsingTask.Parse();
        if (parseResult)
        {
            std::cout << "TRUE" << std::endl;
        }
        else
        {
            std::cout << "FALSE" << std::endl;
        }

        fileStream.close();
    }

    return 0;
}