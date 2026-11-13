#include <iostream>
#include "../graph.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    matf_daa::Graph g(n, false);
    for(int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    std::vector<int> group0 = g.bipartite();
    for(int elem : group0) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
} 