#ifndef MYSOK_H
#define MYSOK_H
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>

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

char board_str[] = {' ', '_', '.', '#', '$', '*', '1', 'u', '2', 'd', 'a'};
std::string move_str[] = {"Up", "Down", "Left", "Right", "Wait"};

// Structure position
typedef struct position
{
  std::vector<std::pair<int, int>> crates;
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
    std::size_t h3 = std::hash<int>{}(s.heuristic);
    std::size_t h4 = std::hash<int>{}(s.g_cost);
    std::size_t h5 = std::hash<int>{}(s.f_eval);

    std::size_t seed = h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3) ^ (h5 << 4);

    for (auto &crate : s.crates)
    {
      std::size_t h6 = std::hash<int>{}(crate.first);
      std::size_t h7 = std::hash<int>{}(crate.second);
      seed ^= h6 ^ (h7 << 1);
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
  std::vector<std::pair<int,int>> crates;
  std::vector<std::pair<int,int>> targets;

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

sok_board_t::sok_board_t()
{
  for (int i = 0; i < NBL; i++)
    for (int j = 0; j < NBC; j++)
      board[i][j] = FREE;
}

void sok_board_t::print_board()
{
  for (int i = 0; i < board_nbl; i++)
  {
    for (int j = 0; j < NBC; j++)
    {
      if (board[i][j] == END_OF_LINE)
        break;
      printf("%c", board_str[board[i][j]]);
    }
    printf("\n");
  }
}

void sok_board_t::move_crates(const state_t &s)
{
  for (int i = 0; i < board_nbl; i++)
  {
    for (int j = 0; j < NBC; j++)
    {
      if (board[i][j] == CRATE_ON_FREE || board[i][j] == MAN1_ON_FREE)
      {
        board[i][j] = FREE;
      }
      else if (board[i][j] == CRATE_ON_TARGET || board[i][j] == MAN1_ON_TARGET)
      {
        board[i][j] = TARGET;
      }
    }
  }

  for (const auto &c : s.crates)
  {
    if (board[c.first][c.second] == TARGET)
    {
      board[c.first][c.second] = CRATE_ON_TARGET;
    }
    if (board[c.first][c.second] == FREE)
    {
      board[c.first][c.second] = CRATE_ON_FREE;
    }
  }

  

  man1_x = s.player1.first;
  man1_y = s.player1.second;

  if (board[man1_x][man1_y] == FREE)
    board[man1_x][man1_y] = MAN1_ON_FREE;
  if (board[man1_x][man1_y] == TARGET)
    board[man1_x][man1_y] = MAN1_ON_TARGET;
}

void sok_board_t::load(char *_file)
{
  FILE *fp = fopen(_file, "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  if (fp == NULL)
  {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  board_nbl = 0;
  nb_crates = 0;
  while ((nread = getline(&line, &len, fp)) != -1)
  {
    if (((int)nread) > 0)
    {
      bool read_ok = false;
      for (int i = 0; i < nread; i++)
      {
        if (line[i] == board_str[FREE])
        {
          board[board_nbl][i] = FREE;
        }
        else if (line[i] == board_str[TARGET])
        {
          board[board_nbl][i] = TARGET;
        }
        else if (line[i] == board_str[WALL])
        {
          read_ok = true;
          board[board_nbl][i] = WALL;
        }
        else if (line[i] == board_str[CRATE_ON_FREE])
        {
          board[board_nbl][i] = CRATE_ON_FREE;
          nb_crates++;
        }
        else if (line[i] == board_str[CRATE_ON_TARGET])
        {
          board[board_nbl][i] = CRATE_ON_TARGET;
          nb_crates++;
        }
        else if (line[i] == board_str[MAN1_ON_FREE])
        {
          man1_x = board_nbl;
          man1_y = i;
          board[board_nbl][i] = MAN1_ON_FREE;
        }
        else if (line[i] == board_str[MAN1_ON_TARGET])
        {
          man1_x = board_nbl;
          man1_y = i;
          board[board_nbl][i] = MAN1_ON_TARGET;
        }
        else if (line[i] == board_str[MAN2_ON_FREE])
        {
          man2_x = board_nbl;
          man2_y = i;
          board[board_nbl][i] = MAN2_ON_FREE;
        }
        else if (line[i] == board_str[MAN2_ON_TARGET])
        {
          man2_x = board_nbl;
          man2_y = i;
          board[board_nbl][i] = MAN2_ON_TARGET;
        }
      }
      if (read_ok)
      {
        board[board_nbl][nread - 1] = END_OF_LINE;
        board_nbl++;
      }
    }
  }
  free(line);
  fclose(fp);
}

#endif
