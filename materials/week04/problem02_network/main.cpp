#include <iostream>
#include "../graph.hpp"

int main() {
    int server_price, cable_price;
    std::cin >> server_price >> cable_price;

    int n, m;
    std::cin >> n >> m;

    matf_daa::Graph g(n, false);
    
    int u, v;
    for(int i = 0; i < m; i++) {
        std::cin >> u >> v;
        g.add_edge(u, v);
    }

    if(server_price <= cable_price) {
        std::cout << n * server_price << std::endl;
    } else {
        std::vector<int> comp_size = g.components_size();
        int price = 0;
        for(int size : comp_size) {
            price += server_price + (size - 1) * cable_price;
        }
        std::cout << price << std::endl;
    }
}   