#include <iostream>
#include "../graph.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    matf_daa::Graph g(n, false);

    int u, v;
    for(int i = 0; i < m; i++) {
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    int root;
    std::cin >> root;

    std::vector<std::pair<int, int>> root_edges = g.dfs(root);

    for(auto& [x, y] : root_edges) {
        std::cout << x << " " << y << std::endl;
    }

    return 0;
}