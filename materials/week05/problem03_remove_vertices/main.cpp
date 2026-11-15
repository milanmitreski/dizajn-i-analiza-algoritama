#include <iostream>
#include "../graph.hpp"

int main() {
    int n, m, q;
    std::cin >> n >> m;

    matf_daa::Graph g(n, false);

    int u, v;
    while(m--) {
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    std::vector<int> cut_vertices = g.cut_vertices();
    std::vector<bool> cut_vertices_info(g.size(), false);

    for(int cut_vertex : cut_vertices) {
        cut_vertices_info[cut_vertex] = true;
    }

    std::cin >> q;
    while(q--) {
        std::cin >> u;
        if(cut_vertices_info[u]) {
            std::cout << "Da " << g.out_degree(u) << std::endl;
        } else {
            std::cout << "Ne" << std::endl;
        }
    }
}