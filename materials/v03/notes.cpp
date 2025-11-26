#include<iostream>
#include<vector>

using namespace std;

class UnionFind {
public:
    UnionFind(int n): m_n(n) {
        m_representative.resize(n);
        m_rang.resize(n);

        for(int i = 0; i < n; i++) {
            m_representative[i] = i;
            m_rang[i] = 0;
        }
    }

    int f(int x) {
        int root = x;
        
        while(this->m_representative[root] != root) {
            root = this->m_representative[root];
        }

        // Sazimanje puteva

        int tmp = x;
        while(tmp != root) {
            int tmp_swap = this->m_representative[tmp];
            this->m_representative[tmp] = root;
            tmp = tmp_swap;
        }

        return root;
    }

    void u(int x, int y) {
        int rx = f(x), ry = f(y);

        if(rx == ry)
            return;
        
        // Uvek zelimo this->m_representative[ry] = rx;
        if(this->m_rang[rx] < this->m_rang[ry])
            swap(rx, ry); // Uvek u ry treba da bude plice drvo
        this->m_representative[ry] = rx;

        if(this->m_rang[rx] == this->m_rang[ry])
            this->m_rang[rx]++;        
    }

    void print() {
        for(int i = 0; i < this->m_n; i++) {
            cout << i << " ";
        }
        cout << endl;
        for(int i = 0; i < this->m_n; i++) {
            cout << this->m_representative[i] << " ";
        }
        cout << endl;
    }
private:
    vector<int> m_representative;
    vector<int> m_rang;
    int m_n;
};

int code(int i, int j, int m) {
    return i * m + j;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> board(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    UnionFind uf(n*m+1);
    const int dummy = n*m; // Implementacioni zahtev

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] == 0) {
                if(i == 0 || j == 0 || i == n-1 || j == m-1) {
                    uf.u(dummy, code(i, j, m));
                } else {
                    if(board[i-1][j] == 0) {
                        uf.u(code(i, j, m), code(i-1, j, m));
                    }
                    if(board[i+1][j] == 0) {
                        uf.u(code(i, j, m), code(i+1, j, m));
                    }
                    if(board[i][j-1] == 0) {
                        uf.u(code(i, j, m), code(i, j-1, m));
                    }
                    if(board[i][j+1] == 0) {
                        uf.u(code(i, j, m), code(i, j+1, m));
                    }
                }
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) {
            if(board[i][j] == 0 && uf.f(dummy) != uf.f(code(i, j, m))) {
                board[i][j] = 1;
            }
        }
    }

    cout << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}