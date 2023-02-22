#ifndef ASTAR_H
#define ASTAR_H
#include "mysok.h"


// ========== Déclarations de fonctions ==========================================
void a_star(state_t &initial, state_t &fin, int n, sok_board_t &sokoban);
template <typename T>
bool isEqual(std::vector<T> &first, std::vector<T> &second);
std::vector<std::pair<int, int> >
next_moves(const state_t &s, sok_board_t &sokoban);
state_t apply_move(state_t s, const std::pair<int, int> &move, sok_board_t &sokoban);
int manhattan_distance(std::pair<int, int> pos1, std::pair<int, int> pos2);
int sum_compute_distances(state_t &state, state_t &final);
bool is_free(std::pair<int, int> pos, sok_board_t &sokoban);
std::pair<int, int> get_closest_target(const state_t &s, const state_t &f);
int heuristic(const state_t &state, const state_t &final_pos);
int compute_g(const state_t &s);
int naive_heuristic(const state_t &s, const state_t &final_pos);
bool is_in_corner(std::pair<int, int> crate, std::pair<int, int> currentpos, sok_board_t &sokoban);
bool is_deadlock(std::pair<int, int> crate, std::pair<int, int> currentpos, sok_board_t &sokoban);

#endif