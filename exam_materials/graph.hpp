#pragma once

#include <vector>

namespace matf_daa {
    class Graph {
    public:
        Graph(size_t n, bool directed);

        void add_edge(int u, int v);
        size_t size();

        enum TopSort { Kahn, DFS };

        size_t in_degree(int v);
        size_t out_degree(int v);

        void dfs();
        void bfs();

        std::vector<int> top_sort(TopSort type);

        std::vector<std::pair<int, int>> bridges();
        std::vector<int> cut_vertices();
    private:
        size_t m_n;
        std::vector<std::vector<int>> m_neighbours;
        bool m_directed;

        void dfs(int v, std::vector<bool>& visited);

        std::vector<int> top_sort_kahn();
        std::vector<int> top_sort_dfs();
        void top_sort_dfs(int v, std::vector<bool>& visited, std::vector<int>& top_sort);

        void bridges_tarjan_dfs(int v, std::vector<bool>& visited, std::vector<int>& preorder, int& preorder_count, std::vector<int>& lowlink, std::vector<int>& dfs_parent, std::vector<std::pair<int, int>>& bridges);
        void cut_vertices_tarjan_dfs(int v, std::vector<bool>& visited, std::vector<int>& preorder, int& preorder_count, std::vector<int>& lowlink, std::vector<int>& dfs_parent, std::vector<int>& cut_vertices);
    };
}
