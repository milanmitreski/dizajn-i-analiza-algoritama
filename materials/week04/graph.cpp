#include "graph.hpp"

#include <iostream>
#include <vector>
#include <queue>

namespace matf_daa {
    Graph::Graph(int n, bool directed): m_n(n), m_neighbours(n), m_directed(directed) {}

    void Graph::add_edge(int u, int v) {
        if(m_directed) {
            m_neighbours[u].push_back(v);
        } else {
            m_neighbours[u].push_back(v);
            m_neighbours[v].push_back(u);
        }
    }

    int Graph::in_degree(int v) {
        if(!m_directed)
            return out_degree(v);
        
        int v_in_degree = 0;

        for(std::vector<int>& neigh : m_neighbours) {
            if(find(neigh.begin(), neigh.end(), v) != neigh.end())
                v_in_degree++;
        }

        return v_in_degree;
    }

    int Graph::out_degree(int v) {
        return m_neighbours[v].size();
    }

    void Graph::dfs() {
        std::vector<bool> visited(m_n, false);

        for(int i = 0; i < m_n; i++) {
            if(!visited[i]) {
                dfs(i, visited);
            }
        }
    }

    void Graph::dfs(int v, std::vector<bool>& visited) {
        visited[v] = true;
        for(int u : m_neighbours[v]) {
            if(!visited[u])
                dfs(u, visited);
        }
    }

    void Graph::bfs() {
        std::queue<int> bfs_queue;
        std::vector<bool> visited(m_n, false);
        int v;

        for(int i = 0; i < m_n; i++) {
            if(visited[i])
                continue;

            visited[i] = true;
            bfs_queue.push(i);

            while(!bfs_queue.empty()) {
                v = bfs_queue.front();
                bfs_queue.pop();

                for(int u : m_neighbours[v]) {
                    if(!visited[u]) {
                        visited[u] = true;
                        bfs_queue.push(u);
                    }
                }
            }
        }
    }
}