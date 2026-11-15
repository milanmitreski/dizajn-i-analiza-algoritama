#include<iostream>
#include "../graph.hpp"
#include<algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;

    matf_daa::Graph g(n, true);

    int u, v;
    while(m--) {
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    std::vector<int> top_sort = g.top_sort(matf_daa::Graph::TopSort::DFS);
    std::vector<std::pair<int, int>> added_edges;
    for(int i = n-1; i >= 0; i--) {
        std::vector<bool> visited = g.connected_with_vertex(i);
        for(int j = i+1; j < n; j++) {
            if(!visited[j]) {
                added_edges.emplace_back(i, j);
            }
        }
    }

    std::sort(added_edges.begin(), added_edges.end());

    for (auto &[u, v] : added_edges) {
        std::cout << u << " " << v << std::endl;
    }
}