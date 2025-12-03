#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Graph {
    Graph(int n, bool directed): m_n(n), m_directed(directed) {
        m_neighbours.resize(n);
    }

    void addEdge(int u, int v) { // Grana u->v (u-v)
        m_neighbours[u].push_back(v);
        if(!m_directed)
            m_neighbours[v].push_back(u);
    }

    void addVertex() {  // Dodaj novi cvor
        this->m_n++;
        this->m_neighbours.resize(this->m_n);
    }

    int inDegree(int u) { // Ulazni stepen cvora
        int deg = 0;
        for(int i = 0; i < this->m_n; i++) { // Idemo kroz svaki cvor
            for(int neighbour : this->m_neighbours[i]) { // I kroz njegove susede
                if(neighbour == u) { // Ako je u sused, dodajemo ulaznu granu za cvor u.
                    deg ++;
                }
            }
        }
        return deg;
    }

    int outDegree(int u) { // Izlazni stepen cvora
        return this->m_neighbours[u].size();
    }

    void dfs(int u) {
        vector<bool> visited(this->m_n, false);
        this->dfs(u, visited);
    }

    void bfs(int u) {
        vector<bool> visited(this->m_n, false);
        
        queue<int> bfs_queue;
        bfs_queue.emplace(u);
        visited[u] = true;
        
        while(!bfs_queue.empty()) {
            int node = bfs_queue.front();
            bfs_queue.pop();

            for(auto neighbour : this->m_neighbours[node])
                if(!visited[neighbour]) {
                    visited[neighbour] = true;
                    bfs_queue.emplace(neighbour);
                }
        }
    }
public:
    vector<vector<int>> m_neighbours;
    int m_n;
    const bool m_directed;

    void dfs(int u, vector<bool>& visited) {
        visited[u] = true;
        // dolazna obrada
        for(int neighbour : this->m_neighbours[u])
            if(!visited[neighbour])
                this->dfs(neighbour, visited);
        // izlazna obrada
    }
};

int main() {

}