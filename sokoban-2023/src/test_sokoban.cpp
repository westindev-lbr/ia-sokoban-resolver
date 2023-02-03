#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;
class Pos
{
public:
    int x, y;
    char n;
    Pos(int xx, int yy, char nn)
    {
        x = xx;
        y = yy;
        n = nn;
    }

    int get_x()
    {
        return x;
    }
    ~Pos() {}
};

struct Map
{
    int xx = 5;
    int yy = 5;
    char **tab;

    Map()
    {
        tab = new char *[yy];
        for (int i = 0; i < yy; ++i)
        {
            tab[i] = nullptr;
        }
        for (int i = 0; i < yy; ++i)
        {
            tab[i] = new char[xx];
        }
        for (int i = 0; i < xx; ++i)
        {
            for (int j = 0; j < yy; ++j)
            {
                if (i == 0 || j == 0 || i == yy - 1 || j == xx - 1)
                {
                    tab[i][j] = '#';
                }
                else
                {
                    tab[i][j] = ' ';
                }
            }
        }
    }

    void clear()
    {
        for (int i = 0; i < yy; i++)
        {
            for (int j = 0; j < xx; j++)
            {
                if (tab[i][j] != '#')
                {
                    tab[i][j] = ' ';
                }
            }
        }
    }

    void place(vector<Pos> pos)
    {
        for (int i = 0; i < pos.size(); i++)
        {
            tab[pos[i].y][pos[i].x] = pos[i].n;
        }
    }

    void affiche(vector<Pos> pos1, vector<Pos> pos2, vector<Pos> pos3)
    { 
        clear();
        place(pos1);
        place(pos2);
        place(pos3);
        for (int i = 0; i < yy; i++)
        {
            cout << "+-+-+-+-+-+" << endl;
            cout << "|";
            for (int j = 0; j < xx; j++)
            {
                cout << tab[i][j] << "|";
            }
            cout << endl;
        }
        cout << "+-+-+-+-+-+" << endl;
       
    }

    char returnCase(int y, int x)
    {
        return tab[y][x];
    }

    bool canMove(int y, int x, int yy, int xx)
    {
        if (returnCase(y, x) != ' ')
        {
            if (returnCase(y, x) == '$')
            {
                if (returnCase(yy, xx) == '#' || returnCase(yy, xx) == '$')
                {
                    return false;
                }
                return true;
            }
            return false;
        }
        return true;
    
    }
};

int indexCaisse(vector<Pos> c, int y, int x)
{
    for (int i = 0; i < c.size(); i++)
    {
        if (y == c[i].y && x == c[i].x)
        {
            return i;
        }
    }

    return -1;
}

void Up(vector<Pos> &p, Map m, vector<Pos> &c, int index)
{
    int y = p[index].y, x = p[index].x;
    if (m.canMove(y - 1, x, y - 2, x))
    {
        p[index].y = y - 1;
        int i = indexCaisse(c, p[index].y, x);
        if (i != -1)
        {
            c[i].y -= 1;
        }
    }
}

void Down(vector<Pos> &p, Map m, vector<Pos> &c, int index)
{
    int y = p[index].y, x = p[index].x;
    if (m.canMove(y + 1, x, y + 2, x))
    {
        p[index].y = y + 1;
        int i = indexCaisse(c, p[index].y, x);
        if (i != -1)
        {
            c[i].y += 1;
        }
    }
}

void Left(vector<Pos> &p, Map m, vector<Pos> &c, int index)
{
    int y = p[index].y, x = p[index].x;
    if (m.canMove(y, x - 1, y, x - 2) == true)
    {
        p[index].x = x - 1;
        int i = indexCaisse(c, y, p[index].x);
        if (i != -1)
        {
            c[i].x -= 1;
        }
    }
}

void Right(vector<Pos> &p, Map m, vector<Pos> &c, int index)
{
    int y = p[index].y, x = p[index].x;
    if (m.canMove(y, x + 1, y, x + 2))
    {
        p[index].x = x + 1;
        int i = indexCaisse(c, y, p[index].x);
        if (i != -1)
        {
            c[i].x += 1;
        }
    }
}

int dist_case(int y, int x, int yy, int xx)
{
    return abs(x - xx) + abs(y - yy);
}

int main()
{
    Map map;
    Pos c1(2, 2, '$');
    Pos p1(1, 3, 'P');
    Pos g1(1, 1, 'X');
    vector<Pos> c;
    vector<Pos> p;
    vector<Pos> g;
    vector<Pos> pos;
    c.push_back(c1);
    p.push_back(p1);
    g.push_back(g1);
    map.affiche(g, p, c);
    Up(p, map, c, 0);
    map.affiche(g, p, c);
    Right(p, map, c, 0);
    map.affiche(g, p, c);
    Right(p, map, c, 0);
    map.affiche(g, p, c);
    Left(p, map, c, 0);
    map.affiche(g, p, c);
    return 0;
}