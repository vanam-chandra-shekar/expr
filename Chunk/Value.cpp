#include "Value.hpp"
#include "mymemory.hpp"

ValueArray::ValueArray()
    : capacity(0) , count(0) , values(nullptr)
{}

ValueArray::~ValueArray() 
{
    if(values != nullptr)
    {
        free(values);
    }
}

ValueArray::ValueArray(ValueArray &&other) 
    : capacity{other.capacity} , count{other.count} , values{other.values}
{   
    other.count = 0;
    other.capacity = 0;
    other.values = nullptr;
}

ValueArray &ValueArray::operator=(ValueArray &&other) {

    free(values);
    capacity = other.capacity;
    count = other.count;
    values = other.values;

    other.capacity = 0;
    other.count = 0;
    other.values = nullptr;

    return *this;
}

void ValueArray::writeValueArray(double value)
{
    if(capacity < count +1)
    {
        int oldCapacity = capacity;
        capacity = GROW_CAPACITY(oldCapacity);
        values = GROW_ARRAY(double , values , oldCapacity , capacity);
    }

    values[count] = value;
    count++;
}