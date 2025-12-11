#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

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
        vector<bool> visited(this->m_n, false);
        this->dfs(u, visited);
    }

    void bfs(int u) {
        vector<bool> visited(this->m_n, false);

        queue<int> bfs_queue;
        bfs_queue.emplace(u);
        visited[u] = true;

        while(!bfs_queue.empty()) {
            int v = bfs_queue.front();
            bfs_queue.pop();
            // dolazna obrada 
            for(int neigbour : this->m_neighbours[v]) {
                if(!visited[neigbour]) {
                    visited[neigbour] = true;
                    bfs_queue.emplace(neigbour);
                }
            }
        }
    }

    enum TopSort {
        Kahn, DFS
    };

    void topSort(TopSort type) {
        if(!this->m_directed) {
            cerr << "Nije mogue topoloski sortirati neusmerni grad" << endl;
            return;
        }

        switch (type)
        {
        case TopSort::Kahn:
            this->kahnTopSort();
            break;
        case TopSort::DFS:
            this->dfsTopSort();
            break;
        }
    }

private:
    int m_n;
    vector<vector<int>> m_neighbours;
    const bool m_directed;

    void dfs(int u, vector<bool>& visited) {
        visited[u] = true;
        // dolazna obrada -- ovde bi implementirali preorder numeraciju
        for(int neighbour : this->m_neighbours[u]) {
            if(!visited[neighbour]) {
                this->dfs(neighbour, visited);
            }
        }
        // izlazna obrada -- ovde bi implementirali postorder numeraciju
    }

    void kahnTopSort() {
        vector<int> inDegrees(this->m_n, 0);
        vector<int> topSort; // v[0], v[1], ..., v[n-1]
        int visited = 0;

        for(int i = 0; i < this->m_n; i++) {
            for(int neighbour : this->m_neighbours[i]) {
                inDegrees[neighbour]++; // imamo granu i->neighbour
            }
        }

        queue<int> zeroInDegree;
        for(int i = 0; i < this->m_n; i++) {
            if(inDegrees[i] == 0) {
                zeroInDegree.push(i);
            }
        }

        while(!zeroInDegree.empty()) {
            int v = zeroInDegree.front();
            zeroInDegree.pop();

            topSort.push_back(v);
            visited++;

            for(int neighbour : this->m_neighbours[v]) {
                inDegrees[neighbour]--;
                if(inDegrees[neighbour] == 0) {
                    zeroInDegree.push(neighbour);
                }
            }
        }

        if(visited == this->m_n) {
            cout << "Topolosko sortiranje grafa: " << endl;
            for(int i = 0; i < this->m_n; i++) {
                cout << topSort[i] << ": " << i+1 << endl;
            }
        } else {
            cerr << "Graf nije DAG" << endl;
        }
    }

    void dfsTopSort() {
        vector<bool> visited(this->m_n, false);
        vector<int> postorder; 

        for(int i = 0; i < this->m_n; i++) {
            if(!visited[i]) {
                dfsTopSort(i, visited, postorder);
            }
        }

        reverse(postorder.begin(), postorder.end());
        cout << "Topolosko sortiranje grafa: " << endl;
        for(int i = 0; i < this->m_n; i++) {
            cout << postorder[i] << ": " << i+1 << endl;
        }
    }

    void dfsTopSort(int u, vector<bool>& visited, vector<int>& postorder) {
        visited[u] = true;
        for(int neighbour: this->m_neighbours[u]) {
            if(!visited[neighbour]) {
                dfsTopSort(neighbour, visited, postorder);
            }
        }
        postorder.push_back(u);
    }
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