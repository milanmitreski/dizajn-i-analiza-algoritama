#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

class SnakesLaddersGraph {
public:
    SnakesLaddersGraph(int n, int k): m_n(n), m_k(k) {
        this->m_neighbours.resize(this->m_n); // Mora da postoji lista susedstva za svaki cvor
    }

    void addEdge(int u, int v) {
        this->m_neighbours[u].push_back(v);
    }

    int shortestGame() {
        vector<int> distance(this->m_n, -1);

        queue<int> bfs_queue;
        bfs_queue.emplace(0);
        distance[0] = 0;

        while(!bfs_queue.empty()) {
            int v = bfs_queue.front();
            bfs_queue.pop();
            // dolazna obrada 

            for(int i = 1; i <= this->m_k && v + i < this->m_n; i++) {
                int next = v + i;

                bool cycle = false;

                while(true) {
                    if(m_neighbours[next].empty()) {
                        break;
                    }

                    next = this->m_neighbours[next][0];

                    if(next == v + i) {
                        cycle = true;
                        break;
                    }
                }

                if(!cycle && distance[next] == -1) {
                    distance[next] = distance[v] + 1;
                    bfs_queue.emplace(next);

                    if(next == this->m_n-1)
                        break;
                }
            }
        }
        
        return distance[this->m_n-1];
    }

private:
    int m_n;
    int m_k;
    vector<vector<int>> m_neighbours;
};

int main() {
    int n, k, m;
    cin >> n >> k >> m;
    SnakesLaddersGraph graph(n, k);

    int start, end;
    for(int i = 0; i < m; i++) {
        cin >> start >> end;
        graph.addEdge(start, end);
    }

    cout << graph.shortestGame() << endl;
}