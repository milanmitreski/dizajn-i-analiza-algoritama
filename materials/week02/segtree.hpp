#pragma once

#include <vector>
#include <functional>

namespace matf_daa {
    template <typename T>
    class SegmentTree {
    public:
        SegmentTree(std::vector<T> array, T neutral, std::function<T(T,T)> operation);
        SegmentTree(std::vector<int> array);

        void point_update(int pos, T value);
        T range_query(int start, int end) const;
        T point_query(int post) const;
        void print() const;

    private:
        std::vector<T> m_tree;
        T m_neutral;
        std::function<T(T, T)> m_operation;

        static int nearest_power(int a, int x);
    };
}