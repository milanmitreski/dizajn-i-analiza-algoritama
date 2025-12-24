#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>

using namespace std;

class WeightedGraph {
    WeightedGraph(int n, bool directed): m_n(n), m_directed(directed) {
        this->m_neighbours.resize(this->m_n);
    }

    void addEdge(int u, int v, int weight) {
        this->m_neighbours[u].emplace_back(v, weight);
        if(!this->m_directed) {
            this->m_neighbours[v].emplace_back(u, weight);
        }
    }

    void addVertex() {
        this->m_n++;
        this->m_neighbours.resize(this->m_n);
    }

    void matrix() {
        vector<vector<int>> matrix(this->m_n, vector<int>(this->m_n, 0));

        for(int i = 0; i < this->m_n; i++) {
            for(auto [neighbour, weight] : this->m_neighbours[i]) {
                matrix[i][neighbour] = weight;
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

    vector<int> dijkstra(int start) {
        vector<bool> visited(this->m_n, false);
        vector<int> distance(this->m_n, INT_MAX);
        vector<int> parent(this->m_n, -1);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
        queue.emplace(0, start);
        distance[start] = 0;

        while(!queue.empty()) {
            auto [dist, vertex] = queue.top();
            queue.pop();

            if(visited[vertex]) {
                continue;
            } else {
                visited[vertex] = true;
            }

            for(auto [neighbour, weight] : this->m_neighbours[vertex]) {
                if(!visited[vertex]) {
                    if (distance[vertex] + weight < distance[neighbour]) {
                        distance[neighbour] = distance[vertex] + weight;
                        parent[neighbour] = vertex;
                        queue.emplace(distance[neighbour], neighbour);
                    }
                }
            }
        }

        return parent;
    }

    vector<int> belmanFord(int start) {
        vector<int> distance(this->m_n, INT_MAX);
        vector<int> parent(this->m_n, -1);
        distance[start] = 0;

        for (int k = 0; k < this->m_n - 1; k++) {
            bool edgesRelaxed = false;
            for (int vertex = 0; vertex < this->m_n; vertex++) {
                for (auto [neighbour, weight] : this->m_neighbours[vertex]) {
                    if (distance[vertex] + weight < distance[neighbour]) {
                        distance[neighbour] = distance[vertex] + weight;
                        parent[neighbour] = vertex;
                        edgesRelaxed = true;
                    }
                }
            }
            if (!edgesRelaxed) break;
        }

        for (int vertex = 0; vertex < this->m_n; vertex++) {
            for (auto [neighbour, weight] : this->m_neighbours[vertex]) {
                if (distance[vertex] + weight < distance[neighbour]) {
                    cout << "Graf sadrzi ciklus negativne duzine" << endl;
                    return {};
                }
            }
        }
        
        return parent;
    }

    vector<int> prim() {
        vector<bool> visited(this->m_n, false);
        vector<int> distance(this->m_n, INT_MAX);
        vector<int> parent(this->m_n, -1);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;

        int start = 0;
        queue.emplace(0, start);
        distance[start] = 0;

        while(!queue.empty()) {
            auto [dist, vertex] = queue.top();
            queue.pop();
        
            if (visited[vertex]) {
                continue;
            } else {
                visited[vertex] = true;
            }
            
            for (const auto& [neighbour, weight] : this->m_neighbours[vertex]) {
                if (!visited[neighbour]) {
                    if (weight < distance[neighbour]) {
                        distance[neighbour] = weight;
                        parent[neighbour] = vertex;
                        queue.emplace(distance[neighbour], neighbour);
                    }
                }
            } 
        }

        return parent;
    }
private:
    int m_n;
    vector<vector<pair<int, int>>> m_neighbours; // (neighbour, weight)
    const bool m_directed;
};

int main() {

}