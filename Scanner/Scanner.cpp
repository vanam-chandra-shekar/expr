#include "Scanner.hpp"
#include "App.hpp"
#include "TokenType.hpp"
#include <string>
#include <unordered_map>

static const std::unordered_map<std::string, TokenType> keywords
{
    {"sin" , TSIN},
    {"cos" , TCOS},
    {"tan" , TTAN},
    {"sqrt",TSQRT},
    {"ln",TLN},
    {"PI" , TPI},
    {"E",TE}
};

bool isAlpha(char c)
{
    return (c >= 'a' && c<= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c)
{
    return c>='0' && c<='9';
}


std::vector<Token> Scanner::scanTokens()
{ 
    while (!isAtEnd())
    {
        start = current;
        scanToken();
    }

    mTokens.emplace_back(pos , TEOF , "" , nullptr);
    return mTokens;
}

Scanner::Scanner(const std::string &src)
    : source{std::move(src)}
{}

void Scanner::scanToken() {
    char c = advance();

    switch (c)
    {
        case '+': addToken(TPLUS); break;
        case '-': addToken(TMINUS); break;
        case '*': addToken(TSTAR); break;
        case '/': addToken(TSLASH); break;
        case '(': addToken(TLEFTPAREN); break;
        case ')': addToken(TRIGHTPAREN); break;
        case '^': addToken(TCARROT); break;

        case ' ':
        case '\n':
        case '\t':
        case '\r':
            break;

        default:
            if(isDigit(c))
            {
                number();
            }
            else if (isAlpha(c))
            {
                keyWord();
            }
            else
            {
                App::error(pos , "Unexpected character.");
            }
    }

    pos++;
}

void Scanner::number() {
    while (isDigit(peek()))
    {
        advance();
    }

    if(peek() == '.' && isDigit(peekNext()))
    {
        advance();
        while (isDigit(peek()))
        {
            advance();
        }
    }

    std::string num = source.substr(start , current - start);
    addToken(TNUMBER , std::stod(num));
}

void Scanner::keyWord() {

    while (isAlpha(peek()))
    {
        advance();
    }

    std::string key = source.substr(start , current - start);
    if(keywords.find(key) == keywords.end())
    {
        App::error(pos , "Unrecognised keyword.");
        return;
    }

    addToken(keywords.at(key));
}
