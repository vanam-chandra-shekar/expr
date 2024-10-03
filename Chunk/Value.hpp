#pragma once

struct ValueArray
{
    int capacity;
    int count;
    double* values;

    ValueArray();
    ~ValueArray();

    ValueArray(ValueArray&& other);
    ValueArray& operator=(ValueArray&& other);

    void writeValueArray(double value);
    inline int size(){return count;}
};