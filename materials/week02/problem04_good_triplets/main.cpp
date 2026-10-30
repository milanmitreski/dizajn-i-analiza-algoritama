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
    matf_daa::SegmentTree<int> left(freq, 0, [](int a, int b) { return a+b; });
    matf_daa::SegmentTree<int> right(freq, 0, [](int a, int b) { return a+b; });
    
    for(int i = 0; i < n; i++) {
        right.point_update(arr[i]-min, right.point_query(arr[i]-min)+1);
    }

    int good_triplets = 0;

    for(int j = 0; j < n; j++) {
        right.point_update(arr[j]-min, right.point_query(arr[j]-min)-1);
        good_triplets += left.range_query(0, arr[j]-min-1) * right.range_query(arr[j]-min+1, max-min);
        good_triplets += right.range_query(0, arr[j]-min-1) * left.range_query(arr[j]-min+1, max-min);
        left.point_update(arr[j]-min, left.point_query(arr[j]-min)+1);
    }

    std::cout << good_triplets << std::endl;
}