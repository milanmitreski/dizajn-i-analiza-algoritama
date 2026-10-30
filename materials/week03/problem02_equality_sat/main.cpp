#include <iostream>
#include "../uf.hpp"

int code(char c) {
    return c - 'a';
}

int main () {
    int n;
    std::cin >> n;

    matf_daa::UnionFind uf(n);

    char x, y;
    std::string op;
    std::vector<std::pair<int, int>> ineq;

    for(int i = 0; i < n; i++) {
        std::cin >> x >> op >> y;
        if(op[0] == '=') {
            uf.unite(code(x), code(y));
        } else { // op[0] == '!'
            ineq.emplace_back(code(x), code(y));
        }
    }

    for(auto& [i, j] : ineq) {
        if(uf.find(i) == uf.find(j)) {
            std::cout << "UNSAT" << std::endl;
            return 0;
        }
    }
    std::cout << "SAT" << std::endl;
    return 0;
}