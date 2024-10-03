#pragma once
#include "Chunk.hpp"
#include <stack>
#include <stdexcept>

struct RunTimeException : public std::runtime_error
{
    explicit RunTimeException(const std::string& messg)
        : std::runtime_error(messg)
    {}
};

class vm
{
private:
    Chunk chunk;
    uint8_t* ip;
    std::stack<double> stack;

public:
    void interpret(Chunk& _chunk);
    void run();
};

