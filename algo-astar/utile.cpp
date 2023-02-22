#include "utile.h"
#include <iostream>


void print_vec_coord(std::vector<std::pair<int, int>> &vec)
{
    for (auto e : vec)
    {
        std::cout << "\t"
                  << "("
                  << e.first << "," << e.second << ")";
    }
    std::cout << std::endl;
}

void print_vec_pair(std::vector<std::pair<std::pair<int, int>, char>> &vec)
{
    for (auto e : vec)
    {
        std::cout << "\t"
                  << "("
                  << e.first.first << "," << e.first.second << ") - " << e.second;
    }
    std::cout << std::endl;
}