#pragma once

#include "TokenType.hpp"
#include <ostream>
#include "string"
#include <variant>

typedef std::variant<std::nullptr_t , double> Value;

struct Token
{
    int mpos;
    TokenType mtype;
    std::string mlexeam;
    Value mliteral;

    Token(int pos , TokenType type , std::string lexeam , Value literal)
        : mpos(pos) , mtype(type) , mlexeam(std::move(lexeam)) , mliteral(std::move(literal))
    {}
};

inline std::string to_string(const Value& val )
{
    if(std::holds_alternative<std::nullptr_t>(val))
    {
        return "null";
    }
    else if (std::holds_alternative<double>(val)) {
        return std::to_string(std::get<double>(val));
    }
    else
    {
        return "Invalid Type";
    }
}

inline std::ostream& operator<<(std::ostream& out , const Token& token)
{   
    out<<token.mpos << " "<<token.mtype << " '"<<token.mlexeam << "' "<<to_string(token.mliteral);

    return out;
}