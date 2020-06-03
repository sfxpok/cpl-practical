#ifndef PARSER_H
#define PARSER_H
#include "scanner.h"

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
    Parser(Scanner &temp)
    {
        scan = &temp;
    }
    ~Parser()
    {
    }

    bool Parse()
    {
        scan->nextToken();
        //return S() && scan->currentToken().isEof();
        return E() && EOF;
    }

    bool E()
    {
        return T() && EE();
    }

    bool EE()
    {
        if (scan->currentToken().getLexem() == "+")
        {
            scan->nextToken();
            return T() && EE();
        }
        else if (scan->currentToken().getLexem() == "-")
        {
            scan->nextToken();
            return T() && EE();
        }
        else
        {
            return true;
        }
    }
    bool T()
    {
        return F() && TT();
    }

    bool TT()
    {
        if (scan->currentToken().getLexem() == "*")
        {
            scan->nextToken();
            return F() && TT();
        }
        else if (scan->currentToken().getLexem() == "/")
        {
            scan->nextToken();
            return F() && TT();
        }
        else if (scan->currentToken().getLexem() == ";")
        {
            scan->nextToken();
            return F() && TT();
        }

        else
        {
            if (scan->currentToken().getToken() == scan->tInteger || scan->currentToken().getToken() == scan->tVariable)
            {
                return F() && TT();
            }
            return true;
        }
    }

    bool F()
    {
        if (scan->currentToken().getLexem() == "(")
        {
            scan->nextToken();
            bool res = E();
            if (res == true && scan->currentToken().getLexem() == ")")
            {
                scan->nextToken();
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (scan->currentToken().getToken() == scan->tVariable)
        {
            scan->nextToken();
            return true;
        }
        else if (scan->currentToken().getLexem() == "#")
        {

            scan->nextToken();

            if (scan->currentToken().getToken() == scan->tFloat)
            {
                return true;
            }
        }
        else if (scan->currentToken().getLexem() == "-")
        {

            scan->nextToken();

            if (scan->currentToken().getLexem() == "#")
            {
                scan->nextToken();

                if (scan->currentToken().getToken() == scan->tFloat)
                {
                    return true;
                }
            }
        }
    }
};
#endif