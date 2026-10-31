#pragma once

#include <iostream>
#include <vector>
#include <functional>

namespace matf_daa {
    template <typename T>
    class SegmentTree {
    public:
        SegmentTree(std::vector<T> array, T neutral, std::function<T(T,T)> operation)
            : m_neutral(neutral), m_operation(operation) {
            size_t n = nearest_power(2, array.size());
            m_tree.resize(2*n, m_neutral);
            
            std::copy(array.begin(), array.end(), std::next(m_tree.begin(), n));
            
            for(size_t i = n-1; i > 0; i--) {
                m_tree[i] = m_operation(m_tree[2*i], m_tree[2*i+1]);
            }
        }

        void point_update(size_t pos, T value) {
            size_t n = m_tree.size() / 2;

            size_t tree_pos = pos + n;
            m_tree[tree_pos] = value;

            for(tree_pos /= 2; tree_pos > 0; tree_pos /= 2) {
                m_tree[tree_pos] = m_operation(m_tree[2*tree_pos], m_tree[2*tree_pos+1]);
            }
        }

        T range_query(size_t start, size_t end) const {
            size_t n = m_tree.size() / 2;
            size_t tree_start = start + n, tree_end = end + n;

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

        T point_query(size_t pos) const {
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

        static size_t nearest_power(unsigned long a, size_t x) {
            size_t n = 1;
            while(n < x) {
                n = n * a;
            }
            return n;
        }
    };
}