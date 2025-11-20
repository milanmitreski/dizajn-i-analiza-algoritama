#include<iostream>
#include<vector>
#include<functional>
#include<climits>

using namespace std;

template <typename T>
class SegmentTree {
public:
    SegmentTree(vector<T> arr, T neutral, function<T(T, T)> operation): m_neutral(neutral), m_operation(operation) {
        int n = nearestPower(2, arr.size());
        m_tree.resize(2*n, m_neutral);
        
        copy(arr.begin(), arr.end(), next(m_tree.begin(), n));

        for(int i = n-1; i >= 1; i--) {
            m_tree[i] = m_operation(m_tree[2*i], m_tree[2*i+1]);
        }
    }

    void pointUpdate(int pos, T value) {
        int n = m_tree.size() / 2;

        int tree_pos = pos + n;
        m_tree[tree_pos] = value;

        for(tree_pos /= 2; tree_pos >= 1; tree_pos /= 2) {
            m_tree[tree_pos] = m_operation(m_tree[2*tree_pos], m_tree[2*tree_pos+1]);
        }
    }

    T rangeQuery(int start, int end) {
        int n = m_tree.size() / 2;
        int tree_start = start + n, tree_end = end + n;

        int result = m_neutral;
        while(tree_start <= tree_end) {
            if(tree_start % 2 == 1)
                result = m_operation(result, m_tree[tree_start++]);
            if(tree_end % 2 == 0)
                result = m_operation(result, m_tree[tree_end--]);
            
            tree_start /= 2;
            tree_end /= 2;
        }

        return result;
    }

    T pointQuery(int pos) {
        return rangeQuery(pos, pos);
    }

    void print() {
        for(T elem: m_tree) {
            cout << elem << " ";
        }
        cout << endl;
    }
private:
    vector<T> m_tree;
    T m_neutral;
    function<T(T, T)> m_operation;

    int nearestPower(int a, int x) {
        int n = 1;
        while(n < x) {
            n = n * a;
        }
        return n;
    }
};

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    int max = INT_MIN;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        if(arr[i] > max)
            max = arr[i];
    }

    vector<int> seg_arr(max+1, 0);
    SegmentTree<int> seg_tree(seg_arr, 0, [](int a, int b) { return a + b; });

    int inversions = 0;
    for(int i = 0; i < n; i++) {
        seg_tree.pointUpdate(arr[i], seg_tree.pointQuery(arr[i]) + 1);
        inversions += seg_tree.rangeQuery(arr[i]+1, max);
    }

    cout << inversions << endl;
}