#ifndef PARSER_H
#define PARSER_H
#include "scanner.h"
#include <iostream>
#include <string>

// Grammar:
// E :: = T EE;
// EE :: = + T EE | - T EE | epsilon;
// T :: = F TT;
// TT :: = * F TT | / F TT | epsilon;
// F :: = (E) | variable | # float | - # float;

class Parser
{

private:
    Scanner *scan;

public:
    Parser(Scanner &scanner_addr)
    {
        scan = &scanner_addr;
    }

    double stringToDouble(std::string strValue)
    {
        return std::stod(strValue);
    }

    bool Parse()
    {

        double tmpVal;
        //double output;

        scan->nextToken();

        //return E(tmpVal);

        std::cout << "Result: " << E(tmpVal) << std::endl;

        if (!scan->currentToken().isEof()) {
            return -1;
        }

        std::cout << "Result: " << tmpVal << std::endl;

        // do
        // { // get all tokens

        //     //scan->nextToken();
        //     tmpVal = scan->nextToken();

        //     Eval = E(Eval);

        //     std::cout << "Result: " << Eval << std::endl;
        // } while (!scan->currentToken().isEof());

        //return E() && EOF;
    }

    bool E(double &outVal)
    {
        double tmpVal;
        return T(tmpVal) && EE(outVal, tmpVal);

        //return T() && EE();
    }

    bool EE(double &outVal, double inVal)
    {
        if (scan->currentToken().getLexem().compare("+") == 0)
        {
            scan->nextToken();
            double tmpVal;
            return T(tmpVal) && EE(outVal, inVal + tmpVal); // inVal + tmpVal becomes 2 + 10 at some point in the runtime
        }
        else if (scan->currentToken().getLexem().compare("-") == 0)
        {
            scan->nextToken();
            double tmpVal;
            return T(tmpVal) && EE(outVal, inVal - tmpVal);
        }
        else
        {
            outVal = inVal; // epsilon
            // note: inVal becomes 12 at some point in runtime
        }
    }

    bool T(double &outVal)
    {
        double tmpVal;
        return F(tmpVal) && TT(outVal, tmpVal);

    }

    bool TT(double &outVal, double inVal)
    {
        if (scan->currentToken().getLexem().compare("*") == 0)
        {
            scan->nextToken();
            double tmpVal;
            return F(tmpVal) && TT(outVal, inVal * tmpVal);

            //return F() && TT();

        }
        else if (scan->currentToken().getLexem().compare("/") == 0)
        {
            scan->nextToken();
            double tmpVal;
            return F(tmpVal) && TT(outVal, inVal / tmpVal);

            //return F() && TT();

        }
        else
        {
            outVal = inVal; // epsilon
            // note: inVal becomes 10 at some point in runtime
            //return true;
        }
    }

    bool F(double &outVal)
    {
        if (scan->currentToken().getLexem().compare("(") == 0)
        {
            scan->nextToken();

            double tmpVal;
            bool temp = E(tmpVal);

            if (temp == true && scan->currentToken().getLexem().compare(")") == 0)
            {
                scan->nextToken();
            }
            else
            {
                return false;
            }
        }
        else if (scan->currentToken().getToken() == scan->tInteger) // change to tVariable
        {

            //scan->nextToken();

            std::string currentLexem = scan->currentToken().getLexem();
            outVal = stringToDouble(currentLexem);
            std::cout << "Double catched: " << outVal << std::endl;

            scan->nextToken();

            //return true;
            //return Fval;
            //return outVal;
        }
        else if (scan->currentToken().getLexem().compare("#") == 0)
        {

            scan->nextToken();

            if (scan->currentToken().getToken() == scan->tFloat)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (scan->currentToken().getLexem().compare("-") == 0)
        {

            scan->nextToken();

            if (scan->currentToken().getLexem().compare("#") == 0)
            {
                scan->nextToken();

                if (scan->currentToken().getToken() == scan->tFloat)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};
#endif