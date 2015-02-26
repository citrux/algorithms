#include <iostream>
#include <queue>
#include <stack>
#include <limits>

#include "graph.hpp"

void dfs(int start, std::vector<int>* G, std::vector<bool> & used)
{
    std::stack<int> s;
    s.push(start);
    used[start] = true;
    while(!s.empty())
    {
        int v = s.top(); s.pop();
        std::cout << v << std::endl;
        for (auto u : G[v])
            if (!used[u])
            {
                s.push(u);
                used[u] = true;
            }
    }
}

void bfs(int start, std::vector<int>* G, std::vector<bool> & used)
{
    std::queue<int> q;
    q.push(start);
    used[start] = true;
    while(!q.empty())
    {
        int v = q.front(); q.pop();
        std::cout << v << std::endl;
        for (auto u : G[v])
            if (!used[u])
            {
                q.push(u);
                used[u] = true;
            }
    }
}
