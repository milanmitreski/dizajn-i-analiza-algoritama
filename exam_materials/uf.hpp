#pragma once

#include <vector>

namespace matf_daa {
    class UnionFind {
    public:
        UnionFind(int n);

        int find(int x);
        void unite(int x, int y);
    private:
        int m_n;
        std::vector<int> m_parent;
        std::vector<int> m_rang;
        std::vector<int> m_size;

        void unite_size(int x, int y);
        void unite_rang(int x, int y);
    };
}