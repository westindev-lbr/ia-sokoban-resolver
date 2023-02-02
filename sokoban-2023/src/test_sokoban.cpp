#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

void clear(char map[][5])
{
    for (int i = 0; i < sizeof(map[0]); i++)
    {
        for (int j = 0; j < sizeof(map[0]); j++)
        {
            if (map[i][j] != '#')
            {
                map[i][j] = ' ';
            }
        }
    }
}

void place(char map[][5], int tab[][2], int choix)
{
    char lettre[3] = {'$', 'P', 'O'};
    for (int i = 0; i < sizeof(tab) / sizeof(tab[0]); i++)
    {
        int a = tab[i][1];
        int b = tab[i][0];
        map[a][b] = lettre[choix];
    }
}
void affiche(char map[][5], int c[][2], int p[][2], int o[][2])
{
    place(map, o, 2);
    place(map, p, 1);
    place(map, c, 0);
    for (int i = 0; i < sizeof(map[0]); i++)
    {
        cout << "+-+-+-+-+-+" << endl;
        cout << "|";
        for (int j = 0; j < sizeof(map[0]); j++)
        {
            cout << map[i][j] << "|";
        }
        cout << endl;
    }
    cout << "+-+-+-+-+-+" << endl;
    clear(map);
}

char returnCase(char map[][5], int a, int b)
{
    return map[a][b];
}

int indexCaisse(int tab[][2], int a, int b)
{
    for (int i = 0; i < sizeof(tab) / sizeof(tab[0]); i++)
    {
        if(a == tab[i][0] && b == tab[i][1]){
            return i;
        }
    }

    return -1;
}

bool canMove(int x, int y,int xx, int yy,char map[][5]){
    if (returnCase(map,y,x) == '#')
    {
        return false;
    }
    if(returnCase(map,y,x) == '$'){
        if(returnCase(map,yy,xx) == '#' || returnCase(map,yy,xx) == '$'){
            return false;
        }
        return true;
    }
    return true;
}

void Up(int p[][2],char map[][5], int c[][2]){
    int a = p[0][0],b = p[0][1];
    if(canMove(a,b-1,a,b-2,map)){
        p[0][1] = b-1;
        int i = indexCaisse(c,a,b-1);
        if(i != -1){
            c[i][1] -= 1;
        }
    }
}

void Down(int p[][2],char map[][5], int c[][2]){
    int a = p[0][0],b = p[0][1];
    if(canMove(a,b+1,a,b+2,map)){
        p[0][1] = b+1;
        int i = indexCaisse(c,a,b+1);
        if(i != -1){
            c[i][1] += 1;
        }
    }
}

void Left(int p[][2],char map[][5], int c[][2]){
    int a = p[0][0],b = p[0][1];
    if(canMove(a-1,b,a-2,b,map)){
        p[0][0] = a-1;
        int i = indexCaisse(c,a-1,b);
        if(i != -1){
            c[i][0] -= 1;
        }
    }
}

void Right(int p[][2],char map[][5], int c[][2]){
    int a = p[0][0],b = p[0][1];
    if(canMove(a+1,b,a+2,b,map)){
        p[0][0] = a+1;
        int i = indexCaisse(c,a+1,b);
        if(i != -1){
            c[i][0] += 1;
        }
    }
}

int dist_case(int a, int b,int c, int d){
    return abs(a-c)+abs(b-d);
}

int main()
{
    char map[5][5] = {{'#', '#', '#', '#', '#'},
                      {'#', ' ', ' ', ' ', '#'},
                      {'#', ' ', ' ', ' ', '#'},
                      {'#', ' ', ' ', ' ', '#'},
                      {'#', '#', '#', '#', '#'}};
    int caisse[1][2] = {{2, 2}};
    int player[1][2] = {{3, 3}};
    int o[1][2] = {{1, 1}};

    affiche(map, caisse, player, o);
    Up(player,map,caisse);
    Left(player,map,caisse);
    affiche(map, caisse, player, o);
    return 0;
}