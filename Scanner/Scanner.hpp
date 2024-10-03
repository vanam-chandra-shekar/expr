#pragma once

#include <vector>
#include "Token.hpp"
#include "TokenType.hpp"

class Scanner
{

public:
    std::vector<Token> scanTokens();
    Scanner(const std::string& src);

private:
    std::string source;
    std::vector<Token> mTokens;
    int start = 0;
    int current = 0;
    int pos = 1;

    void scanToken();

    void number();
    void keyWord();

    inline void addToken(TokenType type , Value value)
    {
        std::string sub = source.substr(start , current - start);
        mTokens.emplace_back(pos , type , std::move(sub) , std::move(value));
    }

    inline void  addToken(TokenType type)
    {
        addToken(type , nullptr);
    }

    inline bool isAtEnd()
    {
        return current >= source.size();
    }

    inline char advance()
    {
        return source.at(current++);
    }

    inline bool match(char expected)
    {
        if(isAtEnd()) return false;
        if(source.at(current) != expected)  return false;

        current++;
        return true;
    }

    inline char peek()
    {
        if(isAtEnd()) return '\0';
        return source.at(current);
    }

    inline char peekNext()
    {
        if(current +1 >= source.size()) return '\0';
        return source.at(current+1);
    }




};