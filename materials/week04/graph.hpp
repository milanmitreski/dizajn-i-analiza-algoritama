#pragma once

#include <vector>

namespace matf_daa {
    class Graph {
    public:
        Graph(int n, bool directed);
        void add_edge(int u, int v);

        int in_degree(int v);
        int out_degree(int v);
        void dfs();
        void bfs();

    private:
        int m_n;
        std::vector<std::vector<int>> m_neighbours;
        bool m_directed;

        void dfs(int v, std::vector<bool>& visited);
    };
}