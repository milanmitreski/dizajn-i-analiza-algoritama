#include "graph.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

namespace matf_daa {
    Graph::Graph(int n, bool directed): m_n(n), m_neighbours(n), m_directed(directed) {}

    void Graph::add_edge(int u, int v) {
        m_neighbours[u].push_back(v);
        if(!m_directed) {
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

    // problem01_root_tree

    std::vector<std::pair<int, int>> Graph::dfs(int v) {
        std::vector<std::pair<int, int>> tree_edges;
        std::vector<bool> visited(m_n, false);

        dfs_tree(v, visited, tree_edges);

        std::sort(tree_edges.begin(), tree_edges.end());

        return tree_edges;
    }

    void Graph::dfs_tree(int v, std::vector<bool>& visited, std::vector<std::pair<int, int>>& tree) {
        visited[v] = true;
        for(int neighbour : m_neighbours[v]) {
            // Fiksirao sam granu (v, neighbour)
            if(!visited[neighbour]) {
                // To je grana DFS drveta
                tree.emplace_back(v, neighbour);
                dfs_tree(neighbour, visited, tree);
            }
        }
    }

    // problem02_network
    std::vector<int> Graph::components_size() {
        std::vector<int> comp_size;
        std::vector<bool> visited(m_n, false);
        int curr_comp_size;
        for(int i = 0; i < m_n; i++) {
            if(!visited[i]) {
                curr_comp_size = 0;
                dfs_components_size(i, visited, curr_comp_size);
                comp_size.push_back(curr_comp_size);
            }
        }
        return comp_size;
    }

    void Graph::dfs_components_size(int v, std::vector<bool>& visited, int& comp_size) {
        visited[v] = true;
        comp_size++; // ulazna obrada

        for(int neighbour : m_neighbours[v]) {
            if(!visited[neighbour]) {
                dfs_components_size(neighbour, visited, comp_size);
            }
        }
    }

    // problem04_bipartite_graph

    std::vector<int> Graph::bipartite() {
        std::vector<int> colors(m_n, -1);
        std::vector<int> group0;
        bool flag = true;
        int color = 0;
        dfs_bipartite(0, colors, color, group0, flag);
        
        if(flag) {
            return group0;
        } else {
            return {};
        }
    }

    void Graph::dfs_bipartite(int v, std::vector<int>& colors, int color, std::vector<int>& group0, bool& flag) {
        colors[v] = color;
        if(color == 0)
            group0.push_back(v);

        for(int neighbour : m_neighbours[v]) {
            if(colors[neighbour] == -1) {
                dfs_bipartite(neighbour, colors, 1-color, group0, flag);    
                if(!flag) return;
            } else if(colors[neighbour] == color) {
                flag = false;
                return;
            }
        }
    }

}