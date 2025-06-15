#include "utils.hpp"
int min(int *arr, int size)
{
    if (size <= 0)
    {
        return -1;
    }
    int min_value = arr[0];
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] < min_value)
        {
            min_value = arr[i];
        }
    }
    return min_value;
}

int max(int *arr, int size)
{
    if (size <= 0)
    {
        return -1;
    }
    int max_value = arr[0];
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }
    return max_value;
}

char to_upper(char c)
{
    return (c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c;
}

bool get_y_or_n(const std::string &prompt)
{
    std::string response;
    while (true)
    {
        std::cout << prompt << " (y/n): ";
        std::cin >> response;
        if (response == "y" || response == "Y")
        {
            return true;
        }
        else if (response == "n" || response == "N")
        {
            return false;
        }
        else
        {
            std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
        }
    }
}

