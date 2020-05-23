#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>

class Token
{
private:
    std::string lexem;
    int column;
    int row;
    int token;
    bool eof;

public:
    Token(const std::string &aLexem, int aColumn, int aRow,
          int aToken, bool aEof)
        : lexem(aLexem), column(aColumn), row(aRow),
          token(aToken), eof(aEof)
    {
    }

    Token() : lexem("")
    {
    }

    const std::string getLexem() const
    {
        return lexem;
    }

    const int getRow() const
    {
        return row;
    }

    const int getColumn() const
    {
        return column;
    }

    const int getToken() const
    {
        return token;
    }

    const bool isEof() const
    {
        return eof;
    }

    friend std::ostream &operator<<(std::ostream &out, const Token &aToken)
    {
        out << "'" << aToken.getLexem() << "' " << aToken.getToken() << " (" << aToken.getRow() << ", " << aToken.getColumn() << ") " << (aToken.isEof() ? "true" : "false");

        return out;
    }
};
#endif // TOKEN_H