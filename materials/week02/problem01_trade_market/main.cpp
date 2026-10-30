#include <iostream>
#include <climits>
#include "../segtree.hpp"

int main() {
    int n, q;
    std::vector<std::pair<int, int>> arr;
    int input;

    std::cin >> n >> q;

    for(int i = 0; i < n; i++) {
        std::cin >> input;
        arr.emplace_back(input, 1);
    }
    std::pair<int, int> neutral = std::make_pair(INT_MIN, 0);
    matf_daa::SegmentTree<std::pair<int, int>> segtree(arr, neutral,
        [](std::pair<int, int> p1, std::pair<int, int> p2) {
            if(p1.first < p2.first) {
                return p2;
            } else if (p2.first < p1.first) {
                return p1;
            } else {
                return std::make_pair(p1.first, p1.second + p2.second);
            }
        });

    char c;
    int a1, a2;
    while(q--) {
        std::cin >> c >> a1 >> a2;
        if(c == 'u') {
            segtree.point_update(a1, std::make_pair(a2, 1));
        } else { // c == 'm'
            std::pair<int, int> result = segtree.range_query(a1, a2);
            std::cout << result.first << " " << result.second << std::endl;
        }
    }
}
