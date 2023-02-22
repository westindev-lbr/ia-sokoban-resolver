#include <iostream>
#include <cstdio>
#include "astar.h"
#include "utile.h"
#include <utility>
#include <ctime>

// =========================== Variables globales ==========================
sok_board_t _sokoban;

// =========================== Program Principal  ==========================
int main(int _ac, char **_av)
{
    // Passage en argument d'un fichier.txt à notre exe
    if (_ac != 2)
    {
        printf("usage: %s SOK_FILE\n", _av[0]);
        return 0;
    }

    std::cout << "Probleme Sokoban : " << _av[1] << std::endl;

    _sokoban.load(_av[1]);
    _sokoban.print_board();
    _sokoban.init_board();

    std::cout << "nb lignes : " << _sokoban.board_nbl << std::endl;
    std::cout << "nb caisses : " << _sokoban.nb_crates << std::endl;
    std::cout << "Coord Joueur : (" << _sokoban.man1_x << ", " << _sokoban.man1_y << ")" << std::endl;

    state_t initial;
    initial.crates = {_sokoban.crates};
    initial.player1.first = _sokoban.man1_x;
    initial.player1.second = _sokoban.man1_y;
    initial.g_cost = 0;
    initial.f_eval = 0;
    initial.heuristic = 0;
    state_t finale;
    finale.crates = {_sokoban.targets};
    state_t new_pos;

    

    new_pos.crates = {{3, 3}, {3, 2}, {3, 1}, {3, 6}, {3, 4}, {3, 5}};

    std::cout << "Position initiale : ";
    print_vec_coord(initial.crates);
    std::cout << "Position finale : ";
    print_vec_coord(finale.crates);

    (isEqual(new_pos.crates, initial.crates)) ? std::cout << "EQUAL" << std::endl : std::cout << "NO EQUAL" << std::endl;

    time_t tstart = clock();
    a_star(initial, finale, 8000, _sokoban);
    time_t tend = clock();
    std::cout << "Temps de calcul : ";
    std::cout << (float)(tend - tstart) / CLOCKS_PER_SEC << " secondes" << std::endl;

    return 0;
}