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

    enum TopSort {
        Kahn, DFS
    };

    vector<int> topSort(TopSort type) {
        if(!this->m_directed) {
            cerr << "Moguce je topoloski sortirati samo usmereni graf!" << endl;
        }

        switch (type)
        {
        case TopSort::Kahn:
            return kahnTopSort();
        case TopSort::DFS:
            return dfsTopSort();
        }
    }

    int num_paths(int s, int t) {
        // TODO
    }

private:
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

    vector<int> kahnTopSort() {
        vector<int> inDegrees(this->m_n, 0);
        vector<int> topSort;
        int visited = 0;

        for(int i = 0; i < this->m_n; i++) {
            for(int neighbour : this->m_neighbours[i]) {
                inDegrees[neighbour]++;
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

            if(visited == this->m_n) {
                cout << "Topolosko sortiranje grafa: " << endl;
                for(int i = 0; i < this->m_n; i++) {
                    cout << topSort[i] << ": " << i+1 << endl;
                }
            } else {
                cout << "Graf nije aciklicki" << endl;
            }
        }

        return topSort;
    }

    vector<int> dfsTopSort() {
        vector<bool> visited(this->m_n, false);
        vector<int> topSort;

        for(int i = 0; i < this->m_n; i++) {
            if(!visited[i]) {
                dfsTopSort(i, visited, topSort);
            }
        }

        reverse(topSort.begin(), topSort.end());
        cout << "Topolosko sortiranje grafa: " << endl;
        for(int i = 0; i < this->m_n; i++) {
            cout << topSort[i] << ": " << i+1 << endl;
        }

        return topSort;
    }
    
    void dfsTopSort(int u, vector<bool>& visited, vector<int>& topSort) {
        visited[u] = true;

        for(int neighbour : this->m_neighbours[u]) {
            if(!visited[neighbour]) {
                dfsTopSort(neighbour, visited, topSort);
            }
        }

        topSort.push_back(u);
    }

    int num_paths(const int s, const int t, const vector<int>& permutation) {
        // TODO
    }
};

int main() {
    // TODO
}