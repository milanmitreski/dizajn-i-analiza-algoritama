#include <iostream>
#include "../segtree.hpp"

int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);

    int min = INT_MAX, max = INT_MIN;

    for(int i = 0; i < n; i++) {
        std::cin >> arr[i];
        if(arr[i] < min) {
            min = arr[i];
        }
        if(arr[i] > max) {
            max = arr[i];
        }
    }

    std::vector<int> freq(max-min+1, 0);
    matf_daa::SegmentTree<int> segtree(freq, 0, [](int a, int b) { return a+b; });
    int total_inversions = 0, curr;

    for(int i = 0; i < n; i++) {
        curr = arr[i];
        total_inversions += segtree.range_query(curr-min+1, max-min);
        segtree.point_update(curr-min, segtree.point_query(curr-min) + 1);
    }

    std::cout << total_inversions << std::endl;

}