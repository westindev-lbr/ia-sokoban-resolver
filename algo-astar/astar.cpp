#include "astar.h"
#include "utile.h"
#include <iostream>
#include <list>
#include <unordered_set>
#include <unordered_map>

void a_star(state_t &initial_pos, state_t &final_pos, int max_iterations, sok_board_t &sokoban)
{

    // Initialisation des structures de données

    std::list<state_t> l{};
    l.push_front(initial_pos);
    std::unordered_map<state_t, state_t, state_hash_t> hash_map;

    // Boucle principale
    int i = 0;
    while (i < max_iterations)
    {

        if (empty(l))
            break;

        state_t s{l.front()};
        l.pop_front();

        sokoban.move_crates(s);
        sokoban.print_board();
        std::cout << std::endl;
        std::cout << "Itération : " << i << std::endl;
        std::cout << "s.g_cost : " << s.g_cost << std::endl;
        std::cout << "s.heur : " << s.heuristic << std::endl;
        std::cout << "s.f_eval : " << s.f_eval << std::endl;
        std::cout << "Coord Joueur : (" << s.player1.first << ", " << s.player1.second << ")" << std::endl;
        std::cout << "Position S : ";
        print_vec_coord(s.crates);
        std::cout << std::endl;

        // Test sokoban résolu
        if (isEqual(s.crates, final_pos.crates))
        {
            std::cout << "Nb d'Itérations effectués  : " << i << std::endl;
            std::cout << "Solution : ";
            print_vec_coord(s.crates);
            return;
        }

        // Initialisation des mouvements possibles du joueur
        std::vector<std::pair<int, int>> moves = next_moves(s, sokoban);
        std::cout << "Moves : ";
        print_vec_coord(moves);

        for (auto &m : moves)
        {

            // Retourne un nouvel état à partir d'un mvt possible
            state_t sbis = apply_move(s, m);
            sbis.g_cost = s.g_cost + 1;                  // Cout de la distance déjà parcourue pour arriver à cet état
            sbis.heuristic = heuristic(sbis, final_pos); // Heuristique, estimation de la distance restante à parcourir pour arriver à l'état final
            sbis.f_eval = sbis.g_cost + sbis.heuristic;  // fonction d'évaluation de g(n) + h(n)

            // Itérateur pour trouver sbis dans la HashMap
            auto it = hash_map.find(sbis);

            // Si pas trouvé dans table
            if (it == hash_map.end())
            {
                hash_map.insert({sbis, s});
                l.push_back(sbis);
                l.sort(state_t_comparator());
            }
            else if (it->second.f_eval > sbis.f_eval)
            {
                hash_map.erase(it);
                hash_map.insert({sbis, s});
                l.push_back(sbis);
                l.sort(state_t_comparator());
            }
        }

        i++;
    }
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

std::vector<std::pair<int, int>>
next_moves(const state_t &s, sok_board_t &sokoban)
{
    std::vector<std::pair<int, int>> moves_array = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};
    std::vector<std::pair<int, int>> moves;

    for (const auto dir : {MOVE_U, MOVE_D, MOVE_L, MOVE_R})
    {
        std::pair<int, int> adjacent_pos{s.player1.first + moves_array[dir].first,
                                         s.player1.second + moves_array[dir].second};

        int adj_cell = sokoban.board[adjacent_pos.first][adjacent_pos.second];
        std::cout << "ADJ_CELL = " << adj_cell << std::endl;

        if (adj_cell == FREE || adj_cell == TARGET)
        {
            moves.push_back(adjacent_pos);
        }
        else if (adj_cell == CRATE_ON_FREE || adj_cell == CRATE_ON_TARGET)
        {
            std::pair<int, int> back_crate_pos{adjacent_pos.first + (adjacent_pos.first - s.player1.first),
                                               adjacent_pos.second + (adjacent_pos.second - s.player1.second)};

            if (is_free(back_crate_pos, sokoban))
            {
                int back_crate_cell = sokoban.board[back_crate_pos.first][back_crate_pos.second];

                if (back_crate_cell == TARGET)
                {
                    moves.push_back(adjacent_pos);
                }
                if (!(is_deadlock(adjacent_pos, back_crate_pos, sokoban)))
                {
                    if (!is_in_corner(adjacent_pos, back_crate_pos, sokoban))
                    {
                        std::cout << "NO CORNER = " << std::endl;
                        moves.push_back(adjacent_pos);
                    }
                }
            }
        }
    }
    // Pas utile de wait pour 1 joueur
    return moves;
}

state_t apply_move(state_t s, const std::pair<int, int> &move)
{
    for (auto &crate : s.crates)
    {
        if ((crate.first == move.first) && (crate.second == move.second))
        {
            std::pair<int, int> back_crate_pos{crate.first + (move.first - s.player1.first),
                                               crate.second + (move.second - s.player1.second)};

            crate.first = back_crate_pos.first;
            crate.second = back_crate_pos.second;
        }
    }

    s.player1.first = move.first;
    s.player1.second = move.second;
    // sokoban.move_crates(s);
    return s;
}

bool is_free(std::pair<int, int> pos, sok_board_t &sokoban)
{
    int cell = sokoban.board[pos.first][pos.second];
    return cell != WALL && cell != CRATE_ON_FREE && cell != CRATE_ON_TARGET;
}

// Calcule la distance de Manhattan entre deux positions
int manhattan_distance(std::pair<int, int> pos1, std::pair<int, int> pos2)
{
    return abs(pos1.first - pos2.first) + abs(pos1.second - pos2.second);
}

// Calcule l'heuristique pour l'état actuel
int sum_compute_distances(state_t &state, state_t &final)
{
    int result = 0;
    for (auto crate : state.crates)
    {
        int closest_distance = INT_MAX;

        for (auto target : final.crates)
        {
            int distance = manhattan_distance(crate, target);
            if (distance < closest_distance)
            {
                closest_distance = distance;
            }
        }

        result += closest_distance;
    }
    return result;
}

std::pair<int, int> get_closest_target(const state_t &s, const state_t &f)
{
    std::pair<int, int> player_pos = s.player1;
    std::pair<int, int> closest_target = f.crates.front();
    int min_distance = manhattan_distance(player_pos, closest_target);

    for (const auto &target : f.crates)
    {
        int dist = manhattan_distance(player_pos, target);
        if (dist < min_distance)
        {
            min_distance = dist;
            closest_target = target;
        }
    }

    return closest_target;
}

int heuristic(const state_t &state, const state_t &final_pos)
{
    // Calcul du coût pour déplacer le joueur vers la caisse la plus proche
    int min_player_to_crate = manhattan_distance(state.player1, get_closest_target(state, final_pos));

    // Calcul du coût pour déplacer chaque caisse vers sa position finale
    int min_crate_to_final = 0;
    for (const auto &crate_pos : state.crates)
    {
        int cost = INT_MAX;
        for (const auto &final : final_pos.crates)
        {
            int final_cost = manhattan_distance(crate_pos, final);
            if (final_cost < cost)
            {
                cost = final_cost;
            }
        }
        min_crate_to_final += cost;
    }

    // L'heuristique est la somme des deux coûts calculés
    return min_player_to_crate + min_crate_to_final;
}

int compute_g(const state_t &s)
{
    int cost = 0;
    // Coût pour atteindre l'état s
    if (!s.crates.empty())
    {
        for (const auto &c : s.crates)
        {
            cost += manhattan_distance(s.player1, c);
        }
    }
    // Coût depuis l'état initial
    cost += s.g_cost;
    return cost;
}

int naive_heuristic(const state_t &s, const state_t &final_pos)
{
    int h = 0;
    for (const auto &c : s.crates)
    {
        int min_dist = std::numeric_limits<int>::max();
        for (const auto &f : final_pos.crates)
        {
            int dist = abs(c.first - f.first) + abs(c.second - f.second);
            if (dist < min_dist)
            {
                min_dist = dist;
            }
        }
        h += min_dist;
    }
    return h;
}

bool is_in_corner(std::pair<int, int> crate, std::pair<int, int> currentpos, sok_board_t &sokoban)
{
    std::vector<std::pair<int, int>> moves_array = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};
    std::vector<std::pair<std::pair<int, int>, char>> around_pos;
    for (const auto dir : {MOVE_U, MOVE_D, MOVE_L, MOVE_R})
    {
        if (crate.first != (currentpos.first + moves_array[dir].first) ||
            crate.second != (currentpos.second + moves_array[dir].second))
        {
            switch (dir)
            {
            case MOVE_U:
                around_pos.push_back({{currentpos.first + moves_array[dir].first,
                                       currentpos.second + moves_array[dir].second},
                                      'u'});
                break;
            case MOVE_D:
                around_pos.push_back({{currentpos.first + moves_array[dir].first,
                                       currentpos.second + moves_array[dir].second},
                                      'd'});
                break;
            case MOVE_L:
                around_pos.push_back({{currentpos.first + moves_array[dir].first,
                                       currentpos.second + moves_array[dir].second},
                                      'l'});
                break;
            case MOVE_R:
                around_pos.push_back({{currentpos.first + moves_array[dir].first,
                                       currentpos.second + moves_array[dir].second},
                                      'r'});
                break;
            default:
                break;
            }
        }
    }

    std::cout << "AROUND POS : ";
    print_vec_pair(around_pos);

    int u = 0, d = 0, l = 0, r = 0;

    // Association Cellule -> Valeur Sokoban
    for (auto &pos : around_pos)
    {
        if (pos.second == 'u')
            u = sokoban.board[pos.first.first][pos.first.second];
        else if (pos.second == 'd')
        {
            d = sokoban.board[pos.first.first][pos.first.second];
        }
        else if (pos.second == 'l')
        {
            l = sokoban.board[pos.first.first][pos.first.second];
        }
        else if (pos.second == 'r')
        {
            r = sokoban.board[pos.first.first][pos.first.second];
        }
    }

    // 2 top corner with WALL, CRATES
    if (u >= WALL && u <= CRATE_ON_TARGET)
    {
        if ((l >= WALL && l <= CRATE_ON_TARGET) || (r >= WALL && r <= CRATE_ON_TARGET))
        {
            return true;
        }
    }
    // 2 bottom corner with WALL, CRATES
    if (d >= WALL && d <= CRATE_ON_TARGET)
    {
        if ((l >= WALL && l <= CRATE_ON_TARGET) || (r >= WALL && r <= CRATE_ON_TARGET))
        {
            std::cout << "JE SUIS LA " << std::endl;
            return true;
        }
    }
    return false;
}

bool is_deadlock(std::pair<int, int> crate, std::pair<int, int> currentpos, sok_board_t &sokoban)
{

    std::pair<int, int> back_crate_pos{currentpos.first + (currentpos.first - crate.first),
                                       currentpos.second + (currentpos.second - crate.second)};

    int cell = sokoban.board[back_crate_pos.first][back_crate_pos.second];
    if (cell == WALL)
    {
        for (auto &target : sokoban.targets)
        {

            if (target.first == (back_crate_pos.first - 2))
            {
                return true;
            }
        }
        return false;
    }
}