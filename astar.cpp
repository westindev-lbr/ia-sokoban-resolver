#include <cstdio>
#include <iostream>
#include "sokoban-2023/src/mysok.h"

using namespace std;

typedef struct coord {
    int x;
    int y;
}Coord;

typedef struct position {
    //std::vector<Coord> v;
    Coord player;
} State;



int main(int _ac, char ** _av)
{
    if (_ac != 2)
    {
        printf("usage: %s SOK_FILE\n", _av[0]);
        return 0;
    }

    cout << "Probleme Sokoban : " << _av[1] << endl;
    sok_board_t Board;
    Board.load(_av[1]);
    Board.print_board();

    cout << "nb : " << Board.board_nbl << endl;
    cout << "Coord Joueur : " << "(" << Board.man1_x << ", " << Board.man1_y << ")" << endl;




    cout << "Hello World" << endl << "J'écris du C++" << endl;
    return 0;
}