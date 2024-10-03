#pragma once

#include "Chunk.hpp"
#include "Token.hpp"
#include <cassert>
#include <vector>

struct ParseError
{
    Token pos;
    std::string_view mssg;
    ParseError(Token _pos, const std::string_view& message)
        : pos{_pos} , mssg{message}
    {}
};


class Parser
{

public:
    std::vector<Token> tokens;
    int current = 0;
    void parse(Chunk& code , std::vector<Token>& _tokens);

private:


    inline bool isAtEnd()
    {
        if(peek().mtype == TEOF) return true;
        return false;
    }

    inline Token peek()
    {
        return tokens.at(current);
    }

    inline Token previous()
    {
        return tokens.at(current-1);
    }

    inline bool check(TokenType type)
    {
        if(isAtEnd()) return false;
        return peek().mtype == type;
    }

    inline Token advance()
    {
        if(!isAtEnd()) current++;
        return previous();
    }

    template<class ... T>
    inline bool match(T ... arg)
    {
        assert((... && std::is_same_v<T,TokenType>));

        if((... || check(arg)))
        {
            advance();
            return true;
        }
        
        return false;
    }

    inline Token consume(TokenType type , std::string_view mssg)
    {
        if(check(type))  return advance();
        throw error(peek() , mssg);
    }

    inline ParseError error(Token token , std::string_view mssg)
    {
        return ParseError(token , mssg);
    }

    void expression(Chunk& out);
    void binary(Chunk& out);
    void term(Chunk& out);
    void unary(Chunk& out);
    void expo(Chunk& out);
    void func(Chunk& out);
    void primary(Chunk& out);


};