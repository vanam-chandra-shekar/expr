#include "Chunk.hpp"

#include "mymemory.hpp"
#include <utility>

Chunk::Chunk()
 : capacity{0} , count{0} , code{nullptr} {}

Chunk::~Chunk() 
{
    if(code != nullptr)
    {
        free(code);
    }
}

Chunk::Chunk(Chunk &&other)
    : capacity{other.capacity} , count{other.count} , code{other.code} , constants{std::move(other.constants)}
{
    other.capacity = 0;
    other.count = 0;
    other.code = nullptr;
}

Chunk &Chunk::operator=(Chunk &&other) {

    free(code);
    count = other.count;
    capacity = other.capacity;
    code = other.code;
    constants = std::move(other.constants);

    other.capacity = 0;
    other.count = 0;
    other.code = nullptr;
    return *this;
}

void Chunk::writeChunk(uint8_t byte) 
{
    if(capacity < count + 1)
    {
        int oldCapcity = capacity;
        capacity = GROW_CAPACITY(oldCapcity);
        code = GROW_ARRAY(uint8_t , code , oldCapcity , capacity);
    }

    code[count] = byte;
    count++;
}

int Chunk::addConstant(double value) 
{
    constants.writeValueArray(value);
    return (constants.count - 1);
}
