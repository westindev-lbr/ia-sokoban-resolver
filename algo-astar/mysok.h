#ifndef MYSOK_H
#define MYSOK_H

#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

#define NBL 20
#define NBC 20
#define MAX_CRATES 20

#define MOVE_U 0
#define MOVE_D 1
#define MOVE_L 2
#define MOVE_R 3
#define MOVE_W 4

#define OUT 0
#define FREE 1
#define TARGET 2
#define WALL 3
#define CRATE_ON_FREE 4
#define CRATE_ON_TARGET 5
#define MAN1_ON_FREE 6
#define MAN1_ON_TARGET 7
#define MAN2_ON_FREE 8
#define MAN2_ON_TARGET 9
#define END_OF_LINE 10



// Structure position
typedef struct position
{
  std::vector<std::pair<int, int> > crates;
  std::pair<int, int> player1;
  int g_cost; 
  int heuristic;
  int f_eval;

  bool operator==(const position &other) const
  {
    return crates == other.crates && player1 == other.player1;
  }

} state_t;

// Fonction de Hashage pour la Hashmap
typedef struct state_hash
{
  std::size_t operator()(const state_t &s) const
  {
    std::size_t h1 = std::hash<int>{}(s.player1.first);
    std::size_t h2 = std::hash<int>{}(s.player1.second);

    std::size_t seed = h1 ^ (h2 << 1);

    for (auto &crate : s.crates)
    {
      std::size_t h3 = std::hash<int>{}(crate.first);
      std::size_t h4 = std::hash<int>{}(crate.second);
      seed ^= h3 ^ (h4 << 1);
    }
    return seed;
  }
} state_hash_t;

struct sok_board_t
{
  int board[NBL][NBC];
  int board_nbl;
  int man1_x;
  int man1_y;
  int man2_x;
  int man2_y;
  int nb_crates;
  std::vector<std::pair<int, int>> crates;
  std::vector<std::pair<int, int>> targets;

  sok_board_t();
  void print_board();
  void load(char *_file);
  void init_board();
  void move_crates(const state_t &s);
};

struct state_t_comparator
{
  bool operator()(const state_t &a, const state_t &b) const
  {
    return a.f_eval < b.f_eval;
  }
};


#endif // MYSOK_H
