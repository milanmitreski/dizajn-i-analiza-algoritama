#include "uf.hpp"

#include <iostream>

namespace matf_daa {
    UnionFind::UnionFind(int n) : m_n(n), m_rang(n, 0), m_size(n, 1), m_parent(n), m_components(n), m_parent_ratio(n, 1.0) {
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
        unite_rang(x, y); 

        // problem05_archipelago: moze i 
        // unite_size(x, y);
    }

    void UnionFind::unite_size(int x, int y) {
        int fx = find(x), fy = find(y);

        if(fx == fy)
            return;

        // problem05_archipelago
        m_components--;
        
        if(m_size[fx] < m_size[fy]) {
            m_parent[fx] = fy;
            m_size[fy] += m_size[fx];
        } else {
            m_parent[fy] = fx;
            m_size[fx] += m_size[fy];
        }
    }

    void UnionFind::unite_rang(int x, int y) {
        float wx, wy;
        int fx = find(x), fy = find(y);

        if(fx == fy)
            return;
        
        // problem05_archipelago
        m_components--;

        if (m_rang[fx] < m_rang[fy]) {
            m_parent[fx] = fy;

            // problem05_archipelago
            m_size[fy] += m_size[fx];
        } else if (m_rang[fy] < m_rang[fx]) {
            m_parent[fy] = fx;

            // problem05_archipelago 
            m_size[fx] += m_size[fy];
        } else {
            m_parent[fy] = fx;
            m_rang[fx]++;

            // problem05_archipelago
            m_size[fx] += m_size[fy];
        }
    }

    // problem05_archipelago
    int UnionFind::get_components() const {
        return m_components;
    }

    int UnionFind::get_size(int x) {
        return m_size[find(x)];
    }

    // problem06_ratios
    int UnionFind::find_with_ratio(int x, float& wx) {
        wx = 1.0;
        while(x != m_parent[x]) {
            m_parent_ratio[x] = m_parent_ratio[x] * m_parent_ratio[m_parent[x]];
            m_parent[x] = m_parent[m_parent[x]];
            
            wx *= m_parent_ratio[x];
            x = m_parent[x];
        }
        return x;
    }

    void UnionFind::unite_with_ratio(int x, int y, float w) {
        float wx, wy;
        int fx = find_with_ratio(x, wx), fy = find_with_ratio(y, wy);

        if(fx == fy)
            return;
        
        if(m_size[fx] < m_size[fy]) {
            m_parent[fx] = fy;
            m_parent_ratio[fx] = w * wy / wx;
            m_size[fy] += m_size[fx];
        } else {
            m_parent[fy] = fx;
            m_parent_ratio[fy] = wx / (w * wy);
            m_size[fx] += m_size[fy];
        }
    }
}