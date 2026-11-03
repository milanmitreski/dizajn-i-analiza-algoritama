#include <iostream>
#include "../uf.hpp"

int main () {
    int n, m;
    std::cin >> n >> m;

    matf_daa::UnionFind uf(n);

    char command;
    int a, b;

    for(int i = 0; i < m; i++) {
        std::cin >> command;

        if(command == 'U') {
            std::cin >> a >> b;
            uf.unite(a, b);
        } else if (command == 'P') {
            std::cin >> a >> b;
            std::cout << (uf.find(a) == uf.find(b) ? "DA" : "NE") << std::endl;
        } else if (command == 'V') {
            std::cin >> a;
            std::cout << uf.get_size(a) << std::endl;
        } else { // command = 'K'
            std::cout << uf.get_components() << std::endl;
        }
    }

    return 0;
}