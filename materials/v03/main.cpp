#include<iostream>
#include<vector>

using namespace std;

class UnionFind {
public:
    UnionFind(int n): m_n(n) {
        m_parent.resize(n);
        m_rang.resize(n);

        for(int i = 0; i < n; i++) {
            m_parent[i] = i;
            m_rang[i] = 0;
        }
    }

    int f(int x) {
        int root = x;

        while(this->m_parent[root] != root)
            root = this->m_parent[root];

        while (x != root) {
            int tmp = this->m_parent[x];
            this->m_parent[x] = root;
            x = tmp;
        }

        return root;
    }

    void u(int x, int y) {
        int fx = f(x), fy = f(y);

        if(fx == fy)
            return;
        
        if(this->m_rang[fx] < this->m_rang[fy])
            swap(fx, fy); // Uvek se preusmerava fy ka fx
        this->m_parent[fy] = fx;

        if(this->m_rang[fx] == this->m_rang[fy])
            this->m_rang[fx]++;
    }

    void print() {
        for(int i = 0; i < this->m_n; i++) {
            cout << i << " ";
        }
        cout << endl;
        for(int i = 0; i < this->m_n; i++) {
            cout << this->m_parent[i] << " ";
        }
        cout << endl;
    }

private:
    vector<int> m_parent;
    vector<int> m_rang;
    int m_n;
};

int code(int i, int j, int m) {
    return i*m+j;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> board(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    UnionFind uf(n*m+1);
    const int dummy = n*m;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] == 0) {
                if(i == 0 || j == 0 || i == n-1 || j == n-1) {
                    uf.u(dummy, code(i, j, m));
                } else {
                    if(i > 0 && board[i-1][j] == 0) {
                        uf.u(code(i,j,m), code(i-1,j,m));
                    }
                    if(i < n-1 && board[i+1][j] == 0) {
                        uf.u(code(i,j,m), code(i+1,j,m));
                    }
                    if(j > 0 && board[i][j-1] == 0) {
                        uf.u(code(i,j,m), code(i,j-1,m));
                    }
                    if(j < m-1 && board[i][j+1] == 0) {
                        uf.u(code(i,j,m), code(i,j+1,m));
                    }
                }
            }
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(board[i][j] == 0 && uf.f(dummy) != uf.f(code(i,j,m)))
                board[i][j] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}