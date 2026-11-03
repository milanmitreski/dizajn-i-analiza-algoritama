#include <iostream>
#include "../uf.hpp"

int code(char c) {
    return c - 'a';
}

int main() {
    int n, q;
    std::cin >> n >> q;
    
    matf_daa::UnionFind uf(26); // 26 = |{'a', 'b',... ,'z'}| 

    char x, y;
    float w;

    for(int i = 0; i < n; i++) {
        std::cin >> x >> y >> w;
        uf.unite_with_ratio(code(x), code(y), w);
    }

    for(int i = 0; i < q; i++) {
        std::cin >> x >> y;
        float wx, wy;
        int fx = uf.find_with_ratio(code(x), wx), fy = uf.find_with_ratio(code(y), wy);
        if(fx == fy) {
            std::cout <<  wx / wy << std::endl;
        } else {
            std::cout << -1 << std::endl;
        }
    }

    return 0;
}