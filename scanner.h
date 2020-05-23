#ifndef SCANNER_H
#define SCANNER_H
#include "token.h"

class Scanner
{
private:
    std::istream *input;
    Token lastToken;
    int row;
    int column;

    const static int maxState = 4;
    const static int startState = 0;
    const static int noEdge = -1;
    int automata[maxState + 1][256];
    int finite[maxState + 1];

    void initAutomata()
    {
        for (int i = 0; i <= maxState; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                automata[i][j] = noEdge;
            }
        }

        for (int i = '0'; i <= '9'; i++)
        {
            automata[0][i] = automata[1][i] = 1;
        }

        automata[0]['+'] = automata[0]['*'] = 2;
        automata[0]['('] = automata[0][')'] = 3;
        automata[0]['\n'] = automata[0][' '] = automata[0]['\t'] = 4;
        automata[4]['\n'] = automata[4][' '] = automata[4]['\t'] = 4;

        finite[0] = tLexError;
        finite[1] = tInteger;
        finite[2] = tOperator;
        finite[3] = tSeparator;
        finite[4] = tIgnore;
    }

protected:
    int getNextState(int aState, int aChar) const
    {
        if (aChar == -1)
        {
            return noEdge;
        }

        return automata[aState][aChar];
    }

    bool isFiniteState(int aState) const
    {
        return finite[aState] != tLexError;
    }

    int getFiniteState(int aState) const
    {
        return finite[aState];
    }

private:
    int peek()
    {
        return input->peek();
    }

    int read()
    {
        int temp = input->get();
        column++;

        if (temp == '\n')
        {
            row++;
            column = 1;
        }

        return temp;
    }

    bool eof()
    {
        return peek() == -1;
    }

    Token nextTokenImp()
    {
        int currentState = startState;
        std::string lexem;
        int startColumn = column;
        int startRow = row;

        do
        {
            int tempState = getNextState(currentState, peek());

            if (tempState != noEdge)
            {
                currentState = tempState;
                lexem += (char)read();
            }
            else
            {
                if (isFiniteState(currentState))
                {
                    Token token(lexem, startColumn, startRow, getFiniteState(currentState), eof());

                    if (token.getToken() == tIgnore)
                    {
                        return nextToken();
                    }
                    else
                    {
                        return token;
                    }
                }
                else
                {
                    return Token("", startColumn, startRow, tLexError, eof());
                }
            }
        } while (true);
    }

public:
    const static int tLexError = -1;
    const static int tIgnore = 0;
    const static int tInteger = 1;
    const static int tOperator = 2;
    const static int tSeparator = 3;

    Scanner(std::istream *aInput)
    {
        row = 1;
        column = 1;
        initAutomata();
        input = aInput;
    }

    Token nextToken()
    {
        return lastToken = nextTokenImp();
    }

    Token currentToken()
    {
        return lastToken;
    }
};
#endif // SCANNER_H