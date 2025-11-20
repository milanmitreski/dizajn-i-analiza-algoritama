#include<iostream>
#include<vector>
#include<functional>
#include<climits>

using namespace std;

template <typename T>
using operation = function<T(T,T)>;

template <typename T>
class SegmentTree {
public:
    SegmentTree(vector<T> arr, T neutral, operation<T> op):
        m_neutral(neutral), m_operation(op) {
            // Najveci stepen broja 2 koji je veci ili jednak od arr.size()
            int n = nearestLargerPower(2, arr.size());
            m_tree.resize(2*n, m_neutral);

            // Popunjavamo segmentno drvo sa elementima niza
            copy(arr.begin(), arr.end(), next(m_tree.begin(), n));

            for(int i = n-1; i >= 1; i--) {
                m_tree[i] = m_operation(m_tree[leftChild(i)], m_tree[rightChild(i)]);
            }
        }

        void pointUpdate(int pos, T value) {
            int n = arrSize();

            int tree_pos = n + pos;
            m_tree[tree_pos] = value;

            for(int i = getParent(tree_pos); i >= 1; i = getParent(i)) {
                m_tree[i] = m_operation(m_tree[leftChild(i)], m_tree[rightChild(i)]);
            }
        }

        T rangeQuery(int start, int end) {
            int n = arrSize(); 
            int tree_start = n + start, tree_end = n + end;

            T result = m_neutral;

            int i_start = tree_start, i_end = tree_end;
            while(i_start <= i_end) {
                if(i_start % 2 == 1) 
                    result = m_operation(m_tree[i_start++], result);
                
                if(i_end % 2 == 0)
                    result = m_operation(result, m_tree[i_end--]);

                i_start = getParent(i_start);
                i_end = getParent(i_end);
            }

            return result;
        }

        T pointQuery(int pos) {
            return this->rangeQuery(pos, pos);
        }

        void print() {
            for(T elem : m_tree) {
                cout << elem << " ";
            }
            cout << endl;
        }
private:
    vector<T> m_tree;
    T m_neutral;
    operation<T> m_operation;

    int arrSize() {
        return m_tree.size() / 2;
    }

    int getParent(int i) {
        return i / 2;
    }

    int leftChild(int i) {
        return 2 * i;
    }

    int rightChild(int i) {
        return 2 * i + 1;
    }

    int nearestLargerPower(int a, int x) {
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