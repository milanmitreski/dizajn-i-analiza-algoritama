#include <iostream>
#include "../uf.hpp"

int code(int i, int j, int n) {
    return i * n + j;
}

int main () {
    int m, n;
    std::cin >> m >> n;
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            std::cin >> matrix[i][j];
        }
    }

    matf_daa::UnionFind uf(m*n+1);
    int dummy = m*n;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] == 0) {
                if(i == 0 || j == 0 || i == m-1 || j == n-1) {
                    uf.unite(dummy, code(i, j, n));
                }
                if (i > 0 && matrix[i - 1][j] == 0) {
                    uf.unite(code(i, j, n), code(i - 1, j, n));
                }
                if (i < m - 1 && matrix[i + 1][j] == 0) {
                    uf.unite(code(i, j, n), code(i + 1, j, n));
                }
                if (j > 0 && matrix[i][j - 1] == 0) {
                    uf.unite(code(i, j, n), code(i, j - 1, n));
                }
                if (j < n - 1 && matrix[i][j + 1] == 0) {
                    uf.unite(code(i, j, n), code(i, j + 1, n));
                }
            }
        }
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(uf.find(dummy) != uf.find(code(i, j, n)))
                matrix[i][j] = 1;
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}