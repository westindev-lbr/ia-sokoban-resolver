#include <iostream>
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <ctime>

#define INF 99999;
using namespace std;

struct Node;
struct Edge;
struct Map;

struct Map
{
    int xx = 8;
    int yy = 7;
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
        for (int i = 0; i < yy; ++i)
        {
            for (int j = 0; j < xx; ++j)
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
            if (seeCase(yy, xx) == '#' || seeCase(yy, xx) == '$')
            {
                return false;
            }
        }
        return true;
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
    int fin, weight;
    string mv;
    Edge(int f, string m)
    {
        fin = f;
        mv = m;
        weight = 1;
    }
};
struct Node
{
    pair<int, int> p;
    vector<pair<int, int>> pi;
    int i;
    char m;
    vector<Edge> edge;
    bool blocked;

    Node(pair<int, int> pos, int index, char move, vector<pair<int, int>> pa)
    {
        p = pos;
        m = move;
        i = index;
        blocked = false;
        pi = pa;
    }

    Node(int index, char move)
    {
        m = move;
        blocked = true;
        i = index;
        p = {-1, -1};
    }

    void seeEdge()
    {
        cout << "source: " << i << endl;
        for (int i = 0; i < edge.size(); i++)
        {
            cout << "->[" << i << "]" << edge[i].fin << "[" << edge[i].mv << "]";
        }
        cout << endl;
    }

    void addEgde(int f, string m)
    {
        Edge eg(f, m);
        edge.push_back(eg);
    }

    int indexPair(int a, int b)
    {
        for (int i = 0; i < pi.size(); i++)
        {
            pair<int, int> c = {a, b};
            if (pi[i] == c)
            {
                return i;
            }
        }
        return -1;
    }

    void seePi()
    {
        for (int i = 0; i < pi.size(); i++)
        {
            cout << pi[i].first << pi[i].second << "_";
        }
        cout << endl;
    }
};

struct Graph
{

    vector<Node> n;

    void addNode(Node node)
    {
        n.push_back(node);
    }

    void seeNode()
    {
        for (int i = 0; i < n.size(); i++)
        {
            n[i].seeEdge();
        }
    }
};

int minDistance(Graph g, vector<int> dist, vector<int> access)
{
    int n = g.n.size();
    int min = INF;
    int min_index;
    int i;
    for (int i = 0; i < n; i++)
        if (access[i] == 0 && dist[i] <= min)
            min = dist[i], min_index = i;
    return min_index;
}

int is_edge_in_adjlist(Graph g, int u, int j)
{
    int test = 0;
    vector<Edge> e = g.n[u].edge;
    for (int i = 0; i < e.size(); i++)
    {
        if (e[i].fin == j)
        {
            test = e[i].weight;
        }
    }

    return test;
}
void show_chemin(int index, vector<int> tab,Graph g,vector<int> &pt)
{
	if (tab[index] == -1)
	{
		printf("\t");
		return;
	}
	show_chemin(tab[index], tab,g, pt);
	// Gare *stat = seeStation(g,index);
	// printf("[(%03d)|%s|%s] ", index,stat->nom,stat->ligne);
    cout<<g.n[index].m<<" ";
    pt.push_back(index);

}

void print_dist(vector<int>tab, int taille, int s, vector<int> chemin, int fin,Graph g, vector<int> &pt)
{
	// Gare *stat1 = seeStation(g,fin);
	// Gare *stat2 = seeStation(g,s);
	// printf("Sommets : \t \t");
	// printf("[(%03d)|%s|%s]\n", fin,stat1->nom,stat1->ligne);
	// printf("Dist. depuis [(%03d)|%s|%s] : \t", s,stat2->nom,stat2->ligne);
	// printf("%d\n", tab[fin]);
	// printf("Chemin. depuis [(%03d)|%s|%s]:", s,stat2->nom,stat2->ligne);
	// show_chemin(fin, chemin,g);
	//printf("\n");
    cout<<"Noeud: "<< fin<<endl;
    cout<<"Distance de puis Noeud"<<s<<": "<<tab[fin]<<endl;
    cout<<"Chemin depuis "<<s<<": ";
    show_chemin(fin, chemin,g, pt);
    cout<<endl;
}

void djikstra(Graph g, int src, int fin, vector<int> &pt)
{
    int n = g.n.size();
    vector<int> dist ;
    vector<int>  acces ;
    vector<int> chemin;
    int inf = INF;
    for (int i = 0; i < n; ++i)
    {
        chemin.push_back(-1);
        dist.push_back(inf);
        acces.push_back(0);
    }
    dist[src] = 0;
    for (int count = 0; count < n - 1; ++count)
    {
        int u = minDistance(g, dist, acces);
        acces[u] = 1;
        for (int j = 0; j < n; ++j)
        {
            if (acces[j] == 0 && is_edge_in_adjlist(g, u, j) != 0 && dist[u] + is_edge_in_adjlist(g, u, j) < dist[j])
            {
                dist[j] = dist[u] + is_edge_in_adjlist(g, u, j);
                chemin[j] = u;
            }
        }
    }

    print_dist(dist, n, src, chemin, fin, g, pt);
    // free(dist);
    // free(acces);
}

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

int goodC(vector<pair<int, int>> ci, vector<pair<int, int>> cf)
{
    int good = 0;
    for (int i = 0; i < ci.size(); i++)
    {
        for (int j = 0; j < cf.size(); j++)
        {
            if (ci[i] == cf[i])
            {
                good += 1;
            }
        }
    }
    return good;
}
int path(vector<Node> &n, vector<pair<int, int>> pf, Map map)
{
    int g = 0;
    for (int i = 0; i < 1000000; i++)
    {
        vector<pair<int, int>> stop;
        while (goodC(n[i].pi, pf) < g)
        {
            i += 1;
        }
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
                    vector<pair<int, int>> pa = n[i].pi;
                    int index = indexCaisse(pa, y - 1, x);
                    if (index != -1)
                    {
                        pa[index].second -= 1;
                    }
                    Node up(pos, size, 'U', pa);
                    if (wasVisited(up, n))
                    {
                        break;
                    }
                    n.push_back(up);
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
                    Node right(pos, size, 'R', pa);
                    if (wasVisited(right, n))
                    {
                        break;
                    }
                    n.push_back(right);
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
                    Node down(pos, size, 'D', pa);
                    if (wasVisited(down, n))
                    {
                        break;
                    }
                    n.push_back(down);
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
                    Node left(pos, size, 'L', pa);
                    if (wasVisited(left, n))
                    {
                        break;
                    }
                    n.push_back(left);
                    n[i].addEgde(size, "L");
                }
                break;
            default:
                break;
            }
        }
        if (isEqual(n[i].pi, pf))
        {
            // dijkstra
            // vec path
            cout << "trouvé trouvé trouvé trouvé trouvé trouvé" << i << endl;
            return i;
        }
        g = goodC(n[i].pi, pf);
    }
    return 0;
}

int main()
{
    clock_t debut, fin;
    srand(time(0));
    Map map;
    vector<pair<int, int>> pi = {{1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}};
    vector<pair<int, int>> pf = {{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}};
    pair<int, int> p1 = {3, 1};
    vector<pair<int, int>> p;
    p.push_back(p1);
    Node src(p1, 0, 'S', pi);
    Graph g;
    g.addNode(src);
    debut = clock();
    int t = path(g.n, pf, map);
    fin = clock();
    cout << (float)(fin - debut) / CLOCKS_PER_SEC << "secondes" << endl;
    p.pop_back();
    p.push_back(g.n[t].p);
    map.affiche(pf, p, g.n[t].pi);
    // chemin(source,result)
    //g.seeNode();
    vector<int> path;
    djikstra(g,0,t,path);
    // cout<<g.n.size()<<endl;
    map.affiche(pf, p, pi);
    for (int i = 0; i < path.size(); i++)
    {
        int ch = path[i];
        vector<pair<int,int>> player;
        player.push_back(g.n[ch].p);
        map.affiche(pf,player,g.n[ch].pi);
    }
    
    // cout << map.tab[3][1] << endl;

    return 0;
}