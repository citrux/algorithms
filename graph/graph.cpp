#include <iostream>
#include <queue>
#include <stack>

#include "graph.hpp"

void dfs(int start, std::vector<int>* G, std::vector<bool> & used)
{
    std::stack<int> s;
    s.push(start);
    while(!s.empty())
    {
        int v = s.top(); s.pop();
        if (!used[v])
        {
            std::cout << v << std::endl;
            used[v] = true;
            for (auto u : G[v])
                s.push(u);
        }
    }
}

void bfs(int start, std::vector<int>* G, std::vector<bool> & used)
{
    std::queue<int> q;
    q.push(start);
    while(!q.empty())
    {
        int v = q.front(); q.pop();
        if (!used[v])
        {
            std::cout << v << std::endl;
            used[v] = true;
            for (auto u : G[v])
                q.push(u);
        }
    }
}
