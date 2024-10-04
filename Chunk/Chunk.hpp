#pragma once
#include "Value.hpp"
#include <cstdint>

enum Opcode
{
    OP_ADD,
    OP_SUB,
    OP_DIV,
    OP_MUL,
    OP_NEG,
    OP_EXPO,
    OP_SIN,
    OP_COS,
    OP_TAN,
    OP_SQRT,
    OP_LN,
    OP_CONSTANT,
    OP_PRINT
};

struct Chunk
{
    int capacity;
    int count;
    uint8_t* code;
    ValueArray constants;

    Chunk();
    ~Chunk();

    Chunk(Chunk&& other);
    Chunk& operator=(Chunk&& other);

    void writeChunk(uint8_t byte);
    int addConstant(double value);
    inline int size(){return count;}
};

