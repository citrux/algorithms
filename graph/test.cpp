#include <iostream>
#include <vector>

#include "graph.hpp"

std::vector<int> G[10] = {
    {1, 2, 3},
    {0, 5, 8},
    {0, 4, 5, 9},
    {0, 7, 8},
    {2, 6},
    {1, 2, 8},
    {4, 9},
    {3, 9},
    {1, 3, 5},
    {2, 6, 7}
};

int main()
{
    std::vector<bool> used(10, false);
    std::cout << "dfs test:" << std::endl;
    dfs(0, G, used);
    std::cout << std::endl;
    std::cout << "bfs test:" << std::endl;
    used.assign(10, false);
    bfs(0, G, used);
}
