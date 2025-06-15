#pragma once

#include <array>
#include <string>
#include <iostream>

typedef unsigned int uint;

char to_upper(char c);

int min(int *arr, int size);
int max(int *arr, int size);

template<typename T>
void print_color(std::ostream &os, const T &value, const std::string &color)
{
    os << "\033[" << color << "m" << value << "\033[0m";
}

constexpr uint pow(uint base, uint exp)
{
    uint result = 1;
    for (uint i = 0; i < exp; ++i)
    {
        result *= base;
    }
    return result;
}

constexpr uint log(uint base, uint value)
{
    uint result = 0;
    while (value > 1)
    {
        value /= base;
        ++result;
    }
    return result;
}


