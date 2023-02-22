#ifndef UTILE_H
#define UTILE_H
#include <vector>
#include <utility>

// Affiche un vecteur de caisses ( x, y)
void print_vec_coord(std::vector<std::pair<int, int>> &vec);
void print_vec_pair(std::vector<std::pair<std::pair<int, int>, char>> &vec);

#endif