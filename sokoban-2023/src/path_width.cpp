#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <ctime>
#include <numeric>

#define INF 99999;
using namespace std;

struct Map
{
    int xx = 8;
    int yy = 7;
    vector<pair<int, int>> cb;
    char tab[7][8] = {{'#', '#', '#', '#', '#', '#', '#', '#'},
                      {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                      {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                      {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                      {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                      {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                      {'#', '#', '#', '#', '#', '#', '#', '#'}};

    Map()
    {
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

    void place(vector<pair<int, int>> pos, char n)
    {
        for (int i = 0; i < pos.size(); i++)
        {
            tab[pos[i].second][pos[i].first] = n;
        }
    }

    void affiche(vector<pair<int, int>> pos1, vector<pair<int, int>> pos2, vector<pair<int, int>> pos3)
    {
        clear();
        place(pos1, '*');
        place(pos2, 'P');
        place(pos3, '$');
        for (int i = 0; i < yy; i++)
        {
            cout << "+-+-+-+-+-+-+-+-+" << endl;
            cout << "|";
            for (int j = 0; j < xx; j++)
            {
                cout << tab[i][j] << "|";
            }
            cout << endl;
        }
        cout << "+-+-+-+-+-+-+-+-+" << endl;
    }

    char seeCase(int y, int x)
    {
        if (y <= 0 || x <= 0 || y >= yy || x >= xx)
        {
            return '#';
        }

        return tab[y][x];
    }

    bool canMove(int y, int x, int yy, int xx)
    {

        if (x <= 0 || y <= 0)
        {
            return false;
        }
        if (seeCase(y, x) == '#')
        {
            return false;
        }
        if (seeCase(y, x) == '$')
        {
            for (int i = 0; i < cb.size(); i++)
            {
                if (xx == cb[i].first && yy == cb[i].second)
                {
                    return false;
                }
            }

            if (seeCase(yy, xx) == '#' || seeCase(yy, xx) == '$')
            {
                return false;
            }
        }
        return true;
    }

    vector<pair<int, int>> CaseBloquer()
    {
        vector<pair<int, int>> cb;
        for (int i = 0; i < yy; i++)
        {
            for (int j = 0; j < xx; j++)
            {
                if (tab[i][j] == ' ')
                {
                    if(!verifyExit(i,j)){
                        cb.push_back({j,i});
                    }
                    if (tab[i + 1][j] == '#' && tab[i][j + 1] == '#')
                    {
                        cb.push_back({j, i});
                    }
                    if (tab[i + 1][j] == tab[i][j - 1] && tab[i + 1][j] == '#')
                    {
                        cb.push_back({j, i});
                    }
                    if (tab[i - 1][j] == tab[i][j - 1] && tab[i - 1][j] == '#')
                    {
                        cb.push_back({j, i});
                    }
                    if (tab[i - 1][j] == tab[i][j + 1] && tab[i - 1][j] == '#')
                    {
                        cb.push_back({j, i});
                    }
                }
            }
        }
        return cb;
    }

    bool verifyObjRow(int i){
        for (int j = 0; j < xx;j++)
        {
            if(tab[i][j] == '*'){
                return true;
            }
        }
        return false;
    }
    bool verifyExit(int y,int x){
       if(seeCase(y+1,x)=='#' && seeCase(y-1,x)!='#'){
            if(verifyObjRow(y)){
                for (int j = 0; j < xx; j++)
                {
                    if(seeCase(y+1,j)!='#' && seeCase(y-1,j)!='#'  ){
                        return true;
                    }
                }  
            }
        }
        if(seeCase(y-1,x)=='#'&& seeCase(y+1,x)!='#'){
            if(verifyObjRow(y)){
                for (int j = 0; j < xx; j++)
                {
                    if(seeCase(y-1,j)!='#' && seeCase(y+1,j)!='#' ){
                        return true;
                    }
                }  
            }
        }
        if(seeCase(y,x+1)=='#' && seeCase(y,x-1)!='#'){
            if(verifyObjCol(x)){
                for (int i = 0; i < yy; i++)
                {
                    if(seeCase(i,x+1)!='#' && seeCase(i,x-1)!='#' ){
                        return true;
                    }
                }  
            }
        }

        if(seeCase(y,x-1)=='#'&& seeCase(y,x+1)!='#'){
            if(verifyObjCol(x)){
                for (int i = 0; i < yy; i++)
                {
                    if(seeCase(i,x-1)!='#' && seeCase(i,x+1)!='#'){
                        return true;
                    }
                }  
            }
        }
       
       return false;
    }
    bool verifyObjCol(int j){
        for (int i = 0; i < yy; i++)
        {
            if(tab[i][j] == '*'){
                return true;
            }
        }
        return false;
    }
};
int indexCaisse(vector<pair<int, int>> c, int y, int x)
{
    for (int i = 0; i < c.size(); i++)
    {
        if (y == c[i].second && x == c[i].first)
        {
            return i;
        }
    }

    return -1;
}

struct Edge
{
    const int weight = 1;
    int f;
    string mv;
    Edge(int fin, string m)
    {
        f = fin;
        mv = m;
    }
};

struct Node
{
    char n;
    pair<int, int> p;
    vector<pair<int, int>> pi;
    vector<Edge> edge;
    int gen;
    int i;
    
    Node(char na,pair<int, int> pp,int gene,int index, vector<pair<int, int>> ppi){
        n = na;
        p = pp;
        gen = gene;
        i = index;
        pi = ppi;
    }

    void addEgde(int f, string m)
    {
        Edge eg(f, m);
        edge.push_back(eg);
    }
};
struct Graph
{
    vector<Node> n;
};

template <typename T>
bool isEqual(std::vector<T> &first, std::vector<T> &second)
{
    if (first.size() != second.size())
    {
        return false;
    }

    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    return first == second;
}

bool wasVisited(Node n, vector<Node> &vn)
{
    for (int i = 0; i < vn.size(); i++)
    {
        if (n.i != vn[i].i)
        {
            if (n.p == vn[i].p && n.pi == vn[i].pi)
            {
                return true;
            }
        }
    }
    return false;
}

int Mnth_dist(pair<int, int> a, pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int calculH(vector<pair<int, int>> pi,vector<pair<int, int>> pf){
    vector<int> h;
    for (int i = 0; i < pi.size(); i++)
    {
        vector<int> acc;
        for (int j = 0; j < pf.size(); j++)
        {
            acc.push_back(Mnth_dist(pi[i],pf[j]));
        }
        h.push_back(*min_element(acc.begin(), acc.end()));
        
    }

    
    
    return accumulate(h.begin(), h.end(), 0);
}

int path(vector<Node> &n, vector<pair<int, int>> pf, Map map)
{
    
    for(int i = 0; i < 10000 ;i++)
    {
        int x = n[i].p.first;
        int y = n[i].p.second;
        map.clear();
        map.place(pf, '*');
        map.place(n[i].pi, '$');
        vector<pair<int, int>> vp = n[i].pi;

        for (int j = 0; j < 4; j++)
        {
            int size = n.size();

            switch (j)
            {
            case 0:

                if (map.canMove(y - 1, x, y - 2, x))
                {
                    pair<int, int> pos = {x, y - 1};
                    vector<pair<int, int>> pa = vp;
                    int index = indexCaisse(pa, y - 1, x);
                    if (index != -1)
                    {
                        pa[index].second -= 1;
                    }
                    Node node('U', pos, n[i].gen+1,size,pa);
                    if (wasVisited(node, n))
                    {
                        break;
                    }
                    n.push_back(node);
                    n[i].addEgde(size, "U");
                }

                break;
            case 1:
                // cout<<map.canMove(y, x + 1, y, x + 2)<<"-"<<i<<"|";
                if (map.canMove(y, x + 1, y, x + 2))
                {
                    pair<int, int> pos = {x + 1, y};
                    vector<pair<int, int>> pa = n[i].pi;
                    int index = indexCaisse(pa, y, x + 1);
                    if (index != -1)
                    {
                        pa[index].first += 1;
                    }
                    Node node('R', pos, n[i].gen+1,size,pa);
                    if (wasVisited(node, n))
                    {
                        break;
                    }
                    n.push_back(node);
                    n[i].addEgde(size, "R");
                }

                break;
            case 2:
                // cout<<map.canMove(y+1,x,y+2,x)<<"-"<<i<<"|";
                if (map.canMove(y + 1, x, y + 2, x))
                {
                    pair<int, int> pos = {x, y + 1};
                    vector<pair<int, int>> pa = n[i].pi;
                    int index = indexCaisse(pa, y + 1, x);
                    if (index != -1)
                    {
                        pa[index].second += 1;
                    }
                    Node node('D', pos, n[i].gen+1,size,pa);
                    if (wasVisited(node, n))
                    {
                        break;
                    }
                    n.push_back(node);
                    n[i].addEgde(size, "D");
                }
                break;
            case 3:
                // cout<<map.canMove(y,x-1,y,x-2)<<"-"<<i<<"|";
                if (map.canMove(y, x - 1, y, x - 2))
                {
                    pair<int, int> pos = {x - 1, y};
                    vector<pair<int, int>> pa = n[i].pi;
                    int index = indexCaisse(pa, y, x - 1);
                    if (index != -1)
                    {
                        pa[index].first -= 1;
                    }
                    Node node('L', pos, n[i].gen+1,size,pa);
                    if (wasVisited(node, n))
                    {
                        break;
                    }
                    n.push_back(node);
                    n[i].addEgde(size, "L");
                }
                break;
            default:
                break;
            }
        }
        if (isEqual(n[i].pi, pf))
        {
            cout << "trouvé trouvé trouvé trouvé trouvé trouvé" << i << endl;
            cout << "Mouvement: "<<n[i].gen<<endl;
            return i;
        }
    }
    return 0;
}

void ReturnPath(vector<Node> n,int index){
    vector<char> rst;
    rst.push_back(n[index].n);
    int tmp = index;

    for (int i = index-1; i > 0; i--)
    {
        for (int j = 0; j < n[i].edge.size(); j++)
        {
            if(tmp == n[i].edge[j].f){
                tmp = i;
                rst.push_back(n[tmp].n);
            }
        }
        
    }
    cout<<"Chemin: ";
    for (int z = rst.size(); z >= 0; z--)
    {
        cout<<" "<<rst[z];
    }
}


int main()
{
    clock_t debut, fin;
    srand(time(0));
    Map map;
    vector<pair<int, int>> pi = {{1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}};
    vector<pair<int, int>> pf = {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}};
    vector<pair<int, int>> p = {{3, 1}};
    map.affiche(pf, p, pi);
    map.cb = map.CaseBloquer();
    Graph g;
    Node n('S',p[0],0,0,pi);
    g.n.push_back(n);
    cout<<calculH(pi,pf)<<endl;
    debut = clock();
    int index = path(g.n,pf,map);
    fin = clock();
    cout << (float)(fin - debut) / CLOCKS_PER_SEC << "secondes" << endl;
    p[0] = g.n[index].p;
    map.affiche(pf,p,g.n[index].pi);
    ReturnPath(g.n,index);
    return 0;
}