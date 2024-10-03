#pragma once

#include <cstddef>
#include <cstdlib>

inline void* reallocate(void* pointer , std::size_t oldCap , std::size_t newCap)
{
    if(newCap == 0)
    {
        free(pointer);
        return nullptr;
    }

    void* result = realloc(pointer , newCap);
    return result;
}

#define GROW_CAPACITY(capacity)\
    ((capacity) < 8 ? 8 : (capacity) * 2)


#define GROW_ARRAY(type , pointer , oldCap , newCap)\
    (type*)reallocate(pointer , sizeof(type) * (oldCap) , sizeof(type) * (newCap))


