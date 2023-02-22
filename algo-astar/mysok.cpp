#include "mysok.h"

char board_str[] = {' ', '_', '.', '#', '$', '*', '1', 'u', '2', 'd', 'a'};
std::string move_str[] = {"Up", "Down", "Left", "Right", "Wait"};

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

void sok_board_t::init_board()
{

    for (int i = 0; i < board_nbl; i++)
    {
        for (int j = 0; j < NBC; j++)
        {
            if (board[i][j] == CRATE_ON_FREE)
            {
                std::pair<int, int> pos_crate{i, j};
                crates.push_back(pos_crate);
            }

            if (board[i][j] == TARGET)
            {
                std::pair<int, int> pos_target{i, j};
                targets.push_back(pos_target);
            }
        }
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

    for (int i = 0; i < (int)s.crates.size(); i++)
    {
        int x = s.crates[i].first;
        int y = s.crates[i].second;

        if (board[x][y] == TARGET)
        {
            board[x][y] = CRATE_ON_TARGET;
        }
        if (board[x][y] == FREE)
        {
            board[x][y] = CRATE_ON_FREE;
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