#include "segtree.hpp"

namespace matf_daa {

    template <typename T>
    SegmentTree<T>::SegmentTree(std::vector<T> array, T neutral, std::function<T(T,T)> operation) : m_neutral(neuutral), m_operation(operation) {
        int n = SegmentTree<T>::nearest_power(2, array.size());
        m_tree.resize(2*n, m_neutral);

        copy(array.begin(), array.end(), next(m_tree.begin(), n));

        for(int i = n-1; i >= 1; i--) {
            m_tree[i] = m_operation(m_tree[2*i], m_tree[2*i+1]);
        }
    }

    SegmentTree<int>::SegmentTree(std::vector<int> array) : SegmentTree(array, 0, [](int a, int b) { return a + b; }) {}

    template <typename T>
    void SegmentTree<T>::point_update(int pos, T value) {
        int n = m_tree.size() / 2;

        int tree_pos = pos + n;
        m_tree[tree_pos] = value;

        for(tree_pos /= 2; tree_pos >= 1; tree_pos /= 2) {
            m_tree[tree_pos] = m_operation(m_tree[2*tree_pos], m_tree[2*tree_pos+1])
        }
    }

    template <typename T>
    T SegmentTree<T>::range_query(int start, int end) const {
        int n = m_tree.size() / 2;
        int tree_start = start + n, tree_end = end + n;

        T result = m_neutral;
        while(tree_start <= tree_end) {
            if(tree_start % 2 == 1) {
                result = m_operation(result, m_tree[tree_start++]);
            }
            if(tree_end % 2 == 0) {
                result = m_operation(result, m_tree[tree_end--]);
            }

            tree_start /= 2;
            tree_end /= 2;
        }

        return result;
    }

    template <typename T>
    T SegmentTree<T>::point_query(int post) const {
        return range_query(pos, pos);
    }

    template <typename T>
    void SegmentTree<T>::print() const {
        for(T elem : m_tree)  {
            cout << elem << " ";
        }
        cout << endl;
    }

    template <typename T>
    int SegmentTree<T>::nearest_power(int a, int x) {
        int n = 1;
        while(n < x) {
            n = n * a;
        }
        return n;
    }
}