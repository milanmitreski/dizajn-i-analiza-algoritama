#include "graph.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdexcept>

namespace matf_daa {
    Graph::Graph(int n, bool directed): m_n(n), m_neighbours(n), m_directed(directed) {}

    void Graph::add_edge(int u, int v) {
        m_neighbours[u].push_back(v);
        if(!m_directed) {
            m_neighbours[v].push_back(u);
        }
    }

    int Graph::size() {
        return this->m_n;
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

    std::vector<int> Graph::top_sort(TopSort type) {
        if(!this->m_directed) {
            throw std::invalid_argument("top_sort: only directed graphs can be sorted topologically");
        }

        switch (type)
        {
        case TopSort::Kahn:
            return top_sort_kahn();
        case TopSort::DFS:
            return top_sort_dfs();
        }
    }

    std::vector<int> Graph::top_sort_kahn() {
        std::vector<int> in_degrees(this->m_n, 0);
        std::vector<int> top_sort;
        int visited = 0;

        for(int i = 0; i < this->m_n; i++) {
            for(int neighbour : this->m_neighbours[i]) {
                in_degrees[neighbour]++;
            }
        }

        std::queue<int> zero_in_degree;

        for(int i = 0; i < this->m_n; i++) {
            if(in_degrees[i] == 0) {
                zero_in_degree.push(i);
            }
        }

        while(!zero_in_degree.empty()) {
            int v = zero_in_degree.front();
            zero_in_degree.pop();

            top_sort.push_back(v);
            visited++;

            for(int u : this->m_neighbours[v]) {
                in_degrees[u]--;
                if(in_degrees[u] == 0) {
                    zero_in_degree.push(u);
                }
            }
        }

        if(visited != this->m_n) {
            throw std::invalid_argument("top_sort: only directed acyclic graphs can be sorted topologically");
        }

        return top_sort;
    }
    
    std::vector<int> Graph::top_sort_dfs() {
        std::vector<bool> visited(this->m_n, false);
        std::vector<int> top_sort;

        for(int i = 0; i < this->m_n; i++) {
            if(!visited[i]) {
                top_sort_dfs(i, visited, top_sort);
            }
        }

        std::reverse(top_sort.begin(), top_sort.end());

        return top_sort;
    }

    void Graph::top_sort_dfs(int v, std::vector<bool>& visited, std::vector<int>& top_sort) {
        visited[v] = true;

        for(int u : this->m_neighbours[v]) {
            if(!visited[u]) {
                top_sort_dfs(u, visited, top_sort);
            }
        }

        top_sort.push_back(v);
    }
    
    std::vector<std::pair<int, int>> Graph::bridges() {
        if(this->m_directed) {
            throw std::invalid_argument("bridges: only undirected graphs are supported");
        }

        std::vector<bool> visited(this->m_n, false);
        std::vector<int> preorder(this->m_n);
        std::vector<int> lowlink(this->m_n);
        std::vector<int> dfs_parent(this->m_n, -1);
        std::vector<std::pair<int, int>> bridges;
        int preorder_count = 0;

        bridges_tarjan_dfs(0, visited, preorder, preorder_count, lowlink, dfs_parent, bridges);

        return bridges;
    }

    void Graph::bridges_tarjan_dfs(int v, std::vector<bool>& visited, std::vector<int>& preorder, int& preorder_count, std::vector<int>& lowlink, std::vector<int>& dfs_parent, std::vector<std::pair<int, int>>& bridges) {
        visited[v] = true;
        preorder[v] = preorder_count++;
        lowlink[v] = preorder[v];

        for(int u : this->m_neighbours[v]) {
            if(visited[u]) {
                if(u != dfs_parent[v] && preorder[u] < lowlink[v]) {
                    lowlink[v] = preorder[u];
                }
            } else {
                dfs_parent[u] = v;
                bridges_tarjan_dfs(u, visited, preorder, preorder_count, lowlink, dfs_parent, bridges);

                if(lowlink[u] < lowlink[v]) {
                    lowlink[v] = lowlink[u];
                }

                if(lowlink[u] > preorder[v]) {
                    bridges.emplace_back(v, u);
                }
            }
        }
    }
    
    std::vector<int> Graph::cut_vertices() {
        if(this->m_directed) {
            throw std::invalid_argument("cut_vertices: only undirected graphs are supported");
        }

        std::vector<bool> visited(this->m_n, false);
        std::vector<int> preorder(this->m_n);
        std::vector<int> lowlink(this->m_n);
        std::vector<int> dfs_parent(this->m_n, -1);
        std::vector<int> cut_vertices;
        int preorder_count = 0;

        cut_vertices_tarjan_dfs(0, visited, preorder, preorder_count, lowlink, dfs_parent, cut_vertices);

        return cut_vertices;
    }

    void Graph::cut_vertices_tarjan_dfs(int v, std::vector<bool>& visited, std::vector<int>& preorder, int& preorder_count, std::vector<int>& lowlink, std::vector<int>& dfs_parent, std::vector<int>& cut_vertices) {
        visited[v] = true;
        preorder[v] = preorder_count++;
        lowlink[v] = preorder[v];

        int child_no = 0;

        for(int u : this->m_neighbours[v]) {
            if(visited[u]) {
                if(u != dfs_parent[v] && preorder[u] < lowlink[v]) {
                    lowlink[v] = preorder[u];
                }
            } else { // !visited[u]
                child_no++;
                dfs_parent[u] = v;
                cut_vertices_tarjan_dfs(u, visited, preorder, preorder_count, lowlink, dfs_parent, cut_vertices);

                if(lowlink[u] < lowlink[v]) {
                    lowlink[v] = lowlink[u];
                }

                if(dfs_parent[v] != -1 && lowlink[u] >= preorder[v]) {
                    cut_vertices.push_back(v);
                }
            }
        }

        if(dfs_parent[v] == -1 && child_no > 1) {
            cut_vertices.push_back(v);
        }
    }

    // problem01_direct_the_edges
    std::vector<int> Graph::top_sort_directed() {
        std::vector<int> in_degrees(this->m_n, 0);
        std::vector<int> top_sort(this->m_n);
        int visited = 0;

        for(int i = 0; i < this->m_n; i++) {
            for(int neighbour : this->m_neighbours[i]) {
                in_degrees[neighbour]++;
            }
        }

        std::queue<int> zero_in_degree;

        for(int i = 0; i < this->m_n; i++) {
            if(in_degrees[i] == 0) {
                zero_in_degree.push(i);
            }
        }

        while(!zero_in_degree.empty()) {
            int v = zero_in_degree.front();
            zero_in_degree.pop();

            top_sort[v] = visited;
            visited++;

            for(int u : this->m_neighbours[v]) {
                in_degrees[u]--;
                if(in_degrees[u] == 0) {
                    zero_in_degree.push(u);
                }
            }
        }

        if(visited != this->m_n) {
            throw std::invalid_argument("top_sort: only directed acyclic graphs can be sorted topologically");
        }

        return top_sort;
    }

    // problem02_add_edges
    std::vector<bool> Graph::connected_with_vertex(int v) {
        std::vector<bool> visited(this->m_n, false);
        for(int u : this->m_neighbours[v]) {
            visited[u] = true;
        }
        return visited;
    }

    // problem04_direct_edges
    void Graph::direct_edges() {
        std::vector<bool> visited(this->m_n, false);
        std::vector<int> preorder(this->m_n);
        std::vector<int> lowlink(this->m_n);
        std::vector<int> dfs_parent(this->m_n, -1);
        std::vector<std::pair<int, int>> bridges;
        int preorder_count = 0;

        bridges_tarjan_dfs(0, visited, preorder, preorder_count, lowlink, dfs_parent, bridges);

        if(bridges.empty()) {
            for(int u = 0; u < this->m_n; u++) {
                for(int v : this->m_neighbours[u]) {
                    if(u > v)
                        continue;
                    
                    int u1 = u, v1 = v;

                    if (preorder[u1] > preorder[v1]) {
                        std::swap(u1, v1);
                    }
                    // Ovde je preorder[u1] < preorder[v1], tj. u je posecen pre v
                    if (dfs_parent[v1] == u1) {
                        std::cout << u1 << " " << v1 << std::endl;
                    } else {
                        // povratna grana
                        std::cout << v1 << " " << u1 << std::endl;
                    }
                }
            }
        } else {
            std::cout << "0" << std::endl;
        }
    }

    // problem06_biconnectedness
    bool Graph::biconnected() {
        std::vector<bool> visited(this->m_n, false);
        std::vector<int> preorder(this->m_n);
        std::vector<int> lowlink(this->m_n);
        std::vector<int> dfs_parent(this->m_n, -1);
        std::vector<int> cut_vertices;
        int preorder_count = 0;

        cut_vertices_tarjan_dfs(0, visited, preorder, preorder_count, lowlink, dfs_parent, cut_vertices);

        // Graf je dvostruko povezan ako je povezan (DFS iz 0 je obisao sve cvorove)
        // i nema artikulacionih tacaka
        return preorder_count == this->m_n && cut_vertices.empty();
    }

}