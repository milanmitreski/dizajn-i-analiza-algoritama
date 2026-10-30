#pragma once

#include <vector>
#include <functional>

namespace matf_daa {
    template <typename T>
    class SegmentTree {
    public:
        SegmentTree(std::vector<T> array, T neutral, std::function<T(T,T)> operation)
            : m_neutral(neutral), m_operation(operation) {
            int n = nearest_power(2, array.size());
            m_tree.resize(2*n, m_neutral);
            
            std::copy(array.begin(), array.end(), std::next(m_tree.begin(), n));
            
            for(int i = n-1; i >= 1; i--) {
                m_tree[i] = m_operation(m_tree[2*i], m_tree[2*i+1]);
            }
        }

        SegmentTree(std::vector<int> array) : SegmentTree(array, 0, [](int a, int b) { return a + b; }) {}

        void point_update(int pos, T value) {
            int n = m_tree.size() / 2;

            int tree_pos = pos + n;
            m_tree[tree_pos] = value;

            for(tree_pos /= 2; tree_pos >= 1; tree_pos /= 2) {
                m_tree[tree_pos] = m_operation(m_tree[2*tree_pos], m_tree[2*tree_pos+1]);
            }
        }

        T range_query(int start, int end) const {
            int n = m_tree.size() / 2;
            int tree_start = start + n, tree_end = end + n;

            T result_left = m_neutral;
            T result_right = m_neutral;
            while(tree_start <= tree_end) {
                if(tree_start % 2 == 1) {
                    result_left = m_operation(result_left, m_tree[tree_start++]);
                }
                if(tree_end % 2 == 0) {
                    result_right = m_operation(m_tree[tree_end--], result_right);
                }

                tree_start /= 2;
                tree_end /= 2;
            }

            return m_operation(result_left, result_right);
        }

        T point_query(int pos) const {
            return range_query(pos, pos);
        }

        void print() const {
            for(T elem : m_tree)  {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }

    private:
        std::vector<T> m_tree;
        T m_neutral;
        std::function<T(T, T)> m_operation;

        static int nearest_power(int a, int x) {
            int n = 1;
            while(n < x) {
                n = n * a;
            }
            return n;
        }
    };
}