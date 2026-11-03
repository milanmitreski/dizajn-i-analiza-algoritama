#include <iostream>
#include "../uf.hpp"

int code(int i, int j, int n) {
    return i * n + j;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<bool>> matrix(n, std::vector<bool>(n, false));
    
    matf_daa::UnionFind uf(n*n + 2);
    int top = n*n, bottom = n*n+1;

    int x, y, min_number_of_ones = -1;

    for(int i = 0; i < m; i++) {
        std::cin >> x >> y;
        matrix[x][y] = true;

        if(x == 0) {
            uf.unite(code(x, y, n), top);
        } else if (x == n-1) {
            uf.unite(code(x, y, n), bottom);
        }

        if (x > 0 && matrix[x-1][y]) {
            uf.unite(code(x, y, n), code(x-1, y, n));
        }
        if (x < n-1 && matrix[x+1][y]) {
            uf.unite(code(x, y, n), code(x+1, y, n));
        }
        if (y > 0 && matrix[x][y-1]) {
            uf.unite(code(x, y, n), code(x, y-1, n));
        }
        if (y < n-1 && matrix[x][y+1]) {
            uf.unite(code(x, y, n), code(x, y+1, n));
        }

        if(min_number_of_ones == -1 && uf.find(top) == uf.find(bottom)) {
            min_number_of_ones = i+1;
        }

    }

    std::cout << min_number_of_ones << std::endl;
    return 0;
}