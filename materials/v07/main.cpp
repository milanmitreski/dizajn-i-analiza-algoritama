#include<iostream>
#include<vector>
#include<queue>
#include<stack>
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

    vector<int> dfsPreorder() {
        vector<bool> visited(this->m_n, false);
        vector<int> preorder;

        for(int i = 0; i < this->m_n; i++) {
            if(!visited[i]) {
                this->dfsPreorder(i, visited, preorder);
            }
        }

        return preorder;
    }

    vector<int> dfsPreorderNumeration() {
        vector<bool> visited(this->m_n, false);
        vector<int> preorder(this->m_n, -1);
        int preorderNo = 0;

        for(int i = 0; i < this->m_n; i++) {
            if(!visited[i]) {
                this->dfsPreorderNumeration(i, visited, preorder, preorderNo);
            }
        }

        return preorder;
    }

    vector<int> dfsPostorder() {
        vector<bool> visited(this->m_n, false);
        vector<int> postorder;

        for(int i = 0; i < this->m_n; i++) {
            if(!visited[i]) {
                this->dfsPostorder(i, visited, postorder);
            }
        }

        return postorder;
    }

    vector<int> dfsPostorderNumeration() {
        vector<bool> visited(this->m_n, false);
        vector<int> postorder(this->m_n, -1);
        int postorderNo = 0;

        for(int i = 0; i < this->m_n; i++) {
            if(!visited[i]) {
                this->dfsPostorderNumeration(i, visited, postorder, postorderNo);
            }
        }

        return postorder;
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

    vector<pair<int, int>> bridges() {
        vector<bool> visited(this->m_n, false);
        vector<int> preorder(this->m_n);
        vector<int> lowlink(this->m_n);
        vector<int> dfsParent(this->m_n, -1);
        vector<pair<int, int>> bridges;
        int preorderNo = 0;

        dfsBridges(0, visited, preorder, preorderNo, lowlink, dfsParent, bridges);
        cout << "Mostovi u datom grafu su: " << endl;
        for(int i = 0; i < bridges.size(); i++) {
            cout << "(" << bridges[i].first << ", " << bridges[i].second << ") " ;
        }
        cout << endl;

        return bridges;
    }

    void cutVertices() {
        vector<bool> visited(this->m_n, false);
        vector<int> preorder(this->m_n);
        vector<int> lowlink(this->m_n);
        vector<int> dfsParent(this->m_n, -1);
        vector<bool> cutVertices(this->m_n, false);
        int preorderNo = 0;

        dfsCutVertices(0, visited, preorder, preorderNo, lowlink, dfsParent, cutVertices);
        cout << "Artikulacione tacke u datom grafu su: " << endl;
        for(int i = 0; i < this->m_n; i++) {
            if(cutVertices[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    enum SCC {
        Tarjan, Kosaraju
    };

    vector<int> scc(SCC type) {
        if(!this->m_directed) {
            cerr << "Moguce je odrediti komponente jake povezanosti samo za usmerene grafove!" << endl;
        }
        
        switch (type)
        {
        case SCC::Tarjan:
            return tarjanSCC();
        case SCC::Kosaraju:
            return kosarajuSCC();
        }
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

    void dfsPreorder(int u, vector<bool>& visited, vector<int>& preorder) {
        visited[u] = true;
        preorder.push_back(u);
        for(int neighbour : this->m_neighbours[u])
            if(!visited[neighbour])
                this->dfsPreorder(neighbour, visited, preorder);
    }

    void dfsPreorderNumeration(int u, vector<bool>& visited, vector<int>& preorder, int& preorderNo) {
        visited[u] = true;
        preorder[u] = preorderNo++;
        for(int neighbour : this->m_neighbours[u])
            if(!visited[neighbour])
                this->dfsPreorderNumeration(neighbour, visited, preorder, preorderNo);
    }

    void dfsPostorder(int u, vector<bool>& visited, vector<int>& postorder) {
        visited[u] = true;
        for(int neighbour : this->m_neighbours[u])
            if(!visited[neighbour])
                this->dfsPostorder(neighbour, visited, postorder);
        postorder.push_back(u);
    }

    void dfsPostorderNumeration(int u, vector<bool>& visited, vector<int>& postorder, int& postorderNo) {
        visited[u] = true;
        for(int neighbour : this->m_neighbours[u])
            if(!visited[neighbour])
                this->dfsPostorderNumeration(neighbour, visited, postorder, postorderNo);
        postorder[u] = postorderNo++;
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

    void dfsBridges(int u, vector<bool>& visited, vector<int>& preorder, int& preorderNo, 
            vector<int>& lowlink, vector<int> dfsParent, vector<pair<int, int>> bridges) {
        visited[u] = true;
        preorder[u] = preorderNo++;
        lowlink[u] = preorder[u];

        for(int neighbour: this->m_neighbours[u]) {
            if(visited[neighbour]) {
                if(neighbour != dfsParent[u] && preorder[neighbour] < lowlink[u]) {
                    lowlink[u] = preorder[neighbour];
                }
            } else {
                dfsParent[neighbour] = u;
                dfsBridges(neighbour, visited, preorder, preorderNo, lowlink, dfsParent, bridges);

                if(lowlink[neighbour] < lowlink[u]) {
                    lowlink[u] = lowlink[neighbour];
                }

                if(lowlink[neighbour] > preorder[u]) {
                    bridges.emplace_back(u, neighbour);
                }
            }
        }
    }

    void dfsCutVertices(int u, vector<bool>& visited, vector<int>& preorder, int& preorderNo, 
            vector<int>& lowlink, vector<int> dfsParent, vector<bool> cutVertices) {
        visited[u] = true;
        preorder[u] = preorderNo++;
        lowlink[u] = preorder[u];

        int childNo = 0;

        for(int neighbour: this->m_neighbours[u]) {
            if(visited[neighbour]) {
                if(neighbour != dfsParent[u] && preorder[neighbour] < lowlink[u]) {
                    lowlink[u] = preorder[neighbour];
                }
            } else {
                childNo++;
                dfsParent[neighbour] = u;
                dfsCutVertices(neighbour, visited, preorder, preorderNo, lowlink, dfsParent, cutVertices);

                if(lowlink[neighbour] < lowlink[u]) {
                    lowlink[u] = lowlink[neighbour];
                }

                if(dfsParent[u] != -1 && lowlink[neighbour] >+ preorder[u]) {
                    cutVertices[u] = true;
                }
            }
        }

        if(dfsParent[u] == -1 && childNo > 1) {
            cutVertices[u] = true;
        }
    }

    vector<int> tarjanSCC() {
        vector<int> components(this->m_n, -1);
        int componentNo = 0;
        vector<int> preorder(this->m_n, -1);
        int preorderNo = 0;
        vector<int> lowlink(this->m_n);
        stack<int> componentVertices;
        vector<bool> onStack(this->m_n, false);

        for(int i = 0; i < this->m_n; i++) {
            if(components[i] == -1) {
                this->dfsTarjanSCC(i, components, componentNo, preorder, preorderNo, lowlink, componentVertices, onStack);
            }
        }

        return components;
    }
    
    void dfsTarjanSCC(int u, vector<int>& components, int& componentNo, vector<int>& preorder,
            int& preorderNo, vector<int>& lowlink, stack<int>& componentVertices, vector<bool>& onStack) {
        preorder[u] = preorderNo++;
        lowlink[u] = preorder[u];
        componentVertices.push(u);
        onStack[u] = true;

        for(int neighbour : this->m_neighbours[u]) {
            if (preorder[neighbour] == -1) {
                this->dfsTarjanSCC(neighbour, components, componentNo, preorder, preorderNo, lowlink, componentVertices, onStack);
                if (lowlink[neighbour] < lowlink[u])
                    lowlink[u] = lowlink[neighbour];
            }
            else if (onStack[neighbour]) {
                if (preorder[neighbour] < lowlink[u]) {
                    lowlink[u] = preorder[neighbour]; 
                }
            }
        }

        if (preorder[u] == lowlink[u]) {
            while (true) {
                int componentVertex = componentVertices.top();
                components[componentVertex] = componentNo;
                onStack[componentVertex] = false;
                componentVertices.pop();
                if (componentVertex == u) {
                    break;
                }
            }
            componentNo++;
        }
    }

    vector<int> kosarajuSCC() {
        vector<int> postorder = this->dfsPostorder();
        vector<vector<int>> transposedNeighbours = this->transposedNeighbours();

        vector<int> components(this->m_n, -1);
        int componentNo = 0;

        for (int i = this->m_n - 1; i >= 0; i--) {
            int v = postorder[i];
            if (components[v] == -1)
                this->dfsTransposedKosarajuSCC(v, components, componentNo++, transposedNeighbours);
        }

        return components;
    }

    vector<vector<int>> transposedNeighbours() {
        vector<vector<int>> transposedNeighbours(this->m_n);

        for(int i = 0; i < this->m_n; i++) {
            for(int neighbour : this->m_neighbours[i]) {
                transposedNeighbours[neighbour].push_back(i);
            }
        }

        return transposedNeighbours;
    }

    void dfsTransposedKosarajuSCC(int u, vector<int>& components, int componentNo, 
                vector<vector<int>> transposedNeighbours) {
        components[u] = componentNo;
        for (int neighbour : transposedNeighbours[u])
            if (components[neighbour] == -1)
                dfsTransposedKosarajuSCC(u, components, componentNo, transposedNeighbours);
    }
};

int main() {

}