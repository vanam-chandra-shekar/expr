#include "debug.hpp"
#include <cstdio>

void disassembleChunk(const Chunk &chunk, const char* name)
{
    printf("===== %s ====\n", name);

    for(int offset=0;offset < chunk.count;)
    {
        offset = disassembleInstruction(chunk , offset);
    }
}

int simpleInstruction(const char* name , int offset)
{
    printf("%s\n" , name);
    return offset+1;
}

int constantInstruction(const char* name , const Chunk& chunk , int offset)
{
    int idx = chunk.code[offset+1];
    printf("%-16s %4d '",name , idx);
    printf("%g",chunk.constants.values[idx]);
    printf("'\n");
    return offset+2;
}

int disassembleInstruction(const Chunk &chunk, int offset)
{
    printf("%04d ",offset);
    uint8_t instruction = chunk.code[offset];

    switch (instruction)
    {
    case OP_ADD:
        return simpleInstruction("OP_ADD", offset);
        break;

    case OP_SUB:
        return simpleInstruction("OP_SUB", offset);
        break;

    case OP_DIV:
        return simpleInstruction("OP_DIV", offset);
        break;

    case OP_MUL:
        return simpleInstruction("OP_MUL", offset);
        break;
    
    case OP_NEG:
        return simpleInstruction("OP_NEG", offset);
        break;

    case OP_EXPO:
        return simpleInstruction("OP_EXPO", offset);
        break;

    case OP_SIN:
        return simpleInstruction("OP_SIN", offset);
        break;

    case OP_COS:
        return simpleInstruction("OP_COS", offset);
        break;

    case OP_TAN:
        return simpleInstruction("OP_TAN", offset);
        break;

    case  OP_PRINT:
        return simpleInstruction("OP_PRINT" , offset);
        break;
    
    case OP_CONSTANT:
        return constantInstruction("OP_CONSTANT" , chunk , offset);
    
    default:
        printf("Unknown opcode %d\n" , instruction);
        return offset+1;
    }
}
