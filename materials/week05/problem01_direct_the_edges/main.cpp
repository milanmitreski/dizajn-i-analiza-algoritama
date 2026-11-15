#include <iostream>
#include "../graph.hpp"

int main() {
    int n, m, p;
    std::cin >> n >> m >> p;

    matf_daa::Graph g(n, true); // = new Graph(n, true);

    int u, v;
    while(m--) {
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    std::vector<int> top_sort_directed = g.top_sort_directed();

    while(p--) {
        std::cin >> u >> v;
        if(top_sort_directed[u] < top_sort_directed[v]) {
            std::cout << u << " " << v << std::endl;
        } else {
            std::cout << v << " " << u << std::endl;
        }
    }

    // delete g;

    return 0;
}