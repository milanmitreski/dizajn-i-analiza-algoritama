#include "uf.hpp"

namespace matf_daa {
    UnionFind::UnionFind(int n) : m_n(n), m_rang(n, 0), m_size(n, 1), m_parent(n) {
        for(int i = 0; i < m_n; i++) {
            m_parent[i] = i;
        }
    }

    int UnionFind::find(int x) {
        while(x != m_parent[x]) {
            m_parent[x] = m_parent[m_parent[x]];
            x = m_parent[x];
        }
        return x;
    }

    void UnionFind::unite(int x, int y) {
        unite_rang(x, y); // unite_size(x, y); 
    }

    void UnionFind::unite_size(int x, int y) {
        int fx = find(x), fy = find(y);

        if(fx == fy)
            return;
        
        if(m_size[fx] < m_size[fy]) {
            m_parent[fx] = fy;
            m_size[fy] += m_size[fx];
        } else {
            m_parent[fy] = fx;
            m_size[fx] += m_size[fy];
        }
    }

    void UnionFind::unite_rang(int x, int y) {
        int fx = find(x), fy = find(y);

        if(fx == fy)
            return;
        
        if (m_rang[fx] < m_rang[fy]) {
            m_parent[fx] = fy;
        } else if (m_rang[fy] < m_rang[fx]) {
            m_parent[fy] = fx;
        } else {
            m_parent[fy] = fx;
            m_rang[fx]++;
        }
    }

}