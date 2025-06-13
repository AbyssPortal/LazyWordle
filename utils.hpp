#pragma once

#include <array>
#include <string>
#include <iostream>

typedef unsigned int uint;

char to_upper(char c);

int min(int *arr, int size);
int max(int *arr, int size);

constexpr uint pow(uint base, uint exp)
{
    uint result = 1;
    for (uint i = 0; i < exp; ++i)
    {
        result *= base;
    }
    return result;
}

