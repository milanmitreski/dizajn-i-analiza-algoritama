#include <iostream>
#include "../graph.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    matf_daa::Graph g(n, false);

    std::vector<int> atmosphere(n);
    for(int i = 0; i < n; i++) {
        std::cin >> atmosphere[i];
    }

    int u, v;
    while(m--) {
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    std::vector<int> cut_vertices = g.cut_vertices();
    // cut_vertices moze da sadrzi isti cvor vise puta (jednom za svako dete
    // koje odvaja), pa koristimo niz indikatora da svaki cvor brojimo jednom
    std::vector<bool> cut_vertices_info(g.size(), false);

    for(int cut_vertex : cut_vertices) {
        cut_vertices_info[cut_vertex] = true;
    }

    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(cut_vertices_info[i]) {
            sum += atmosphere[i];
        }
    }

    if(sum > 0) {
        std::cout << "POZITIVNA " << sum << std::endl;
    } else {
        std::cout << "NEGATIVNA " << -sum << std::endl;
    }

    return 0;
}
