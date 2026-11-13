#pragma once

#include <vector>

namespace matf_daa {
    class Graph {
    public:
        Graph(int n, bool directed);
        void add_edge(int u, int v);

        enum TopSort { Kahn, DFS };

        int in_degree(int v);
        int out_degree(int v);
        void dfs();
        void bfs();

        // problem01_root_tree
        std::vector<std::pair<int, int>> dfs(int v);

        // problem02_network
        std::vector<int> components_size();

        // problem04_bipartite_graph;
        std::vector<int> bipartite(); 

    private:
        int m_n;
        std::vector<std::vector<int>> m_neighbours;
        bool m_directed;

        void dfs(int v, std::vector<bool>& visited);
        
        // problem01_root_tree
        void dfs_tree(int v, std::vector<bool>& visited, std::vector<std::pair<int, int>>& tree);

        // problem02_network
        void dfs_components_size(int v, std::vector<bool>& visited, int& comp_size);

        // problem04_bipartite_graph
        void dfs_bipartite(int v, std::vector<int>& colors, int color, std::vector<int>& group0, bool& flag);
    };
}