#include <iostream>
#include "../uf.hpp"

int main() {
    int n, m;
    std::cin >> n >> m;

    matf_daa::UnionFind uf(n);

    char option;
    int x, y;

    while(m--) {
        std::cin >> option >> x >> y;

        if(option == 'T') {
            uf.unite(x, y);
        } else { // option = 'Q'
            std::cout << (uf.find(x) == uf.find(y) ? "DA" : "NE") << std::endl;
        }
    }

    return 0;
}