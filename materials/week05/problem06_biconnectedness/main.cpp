#include <iostream>
#include "../graph.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    matf_daa::Graph g(n, false);

    int u, v;
    while(m--) {
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    if(g.biconnected()) {
        std::cout << "Da" << std::endl;
    } else {
        std::cout << "Ne" << std::endl;
    }

    return 0;
}
