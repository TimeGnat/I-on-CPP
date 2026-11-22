
#pragma once
#include <iostream>

enum class DataType : uint8_t {
    Int,
    Float,
    Double,
    CHAR,
    BOOL
};

template <typename T>
#pragma pack(push, 1)
struct Variable 
{
    T value;           
    DataType type;     
};
#pragma pack(pop)