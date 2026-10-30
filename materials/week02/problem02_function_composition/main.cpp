#include<iostream>
#include"../segtree.hpp"

int main() {
    int n, q;
    std::vector<std::pair<int, int>> functions;
    int a, b;

    std::cin >> n >> q;

    for(int i = 0; i < n; i++) {
        std::cin >> a >> b;
        functions.emplace_back(a, b);
    }

    std::pair<int, int> neutral = std::make_pair(1, 0);
    matf_daa::SegmentTree<std::pair<int, int>> segtree(functions, neutral,
        [](std::pair<int, int> f1, std::pair<int, int> f2) {
            return std::make_pair(f1.first * f2.first, f1.second * f2.first + f2.second);
        });

    int type, a1, a2, a3;
    while(q--) {
        std::cin >> type >> a1 >> a2 >> a3;
        if(type == 0) {
            segtree.point_update(a1, std::make_pair(a2, a3));
        } else { // type == 1
            std::pair<int, int> result = segtree.range_query(a1, a2);
            std::cout << result.first * a3 + result.second << std::endl;
        }
    }
}