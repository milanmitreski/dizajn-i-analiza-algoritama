#include<iostream>
#include<vector>

using namespace std;

class Graph {
public:
    Graph(int n, bool directed): m_n(n), m_directed(directed) {
        this->m_neighbours.resize(this->m_n); // Mora da postoji lista susedstva za svaki cvor
    }

    void addEdge(int u, int v) {
        this->m_neighbours[u].push_back(v);
        if(!this->m_directed) {
            this->m_neighbours[v].push_back(u);
        }
    }

    void addVertex() {
        this->m_n++;
        this->m_neighbours.resize(this->m_n);
    }

    // Vezba - kreirati matricu povezanosti
    void matrix() {
        vector<vector<bool>> matrix(this->m_n, vector<bool>(this->m_n, false));

        for(int i = 0; i < this->m_n; i++) {
            for(int neighbour : this->m_neighbours[i]) {
                matrix[i][neighbour] = true;
            }
        }

        for(auto row : matrix) {
            for(auto elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void dfs(int u) {
        // TODO
    }

    void bfs(int u) {
        // TODO
    }
private:
    int m_n;
    vector<vector<int>> m_neighbours;
    const bool m_directed;
};

int main() {
    Graph g(5, false);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.matrix();
}