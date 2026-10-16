#include "trie.hpp"
#include <iostream>

namespace matf_daa {
    Trie::TrieNode::TrieNode() : wordend(false), count(0) {}

    Trie::Trie() {
        root = new TrieNode();
    }

    Trie::~Trie() {
        clear(root);
    }

    void Trie::insert(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (!current->children.contains(ch)) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->wordend = true;

        // problem02_word_freq
        current->count++;
    }

    bool Trie::find(const std::string& word) const {
        TrieNode* current = root;
        for (char ch : word) {
            if (!current->children.contains(ch)) {
                return false;
            }
            current = current->children[ch];
        }
        return current->wordend;
    }

    void Trie::clear(TrieNode* node) {
        if (node == nullptr) return;
        for (auto& pair : node->children) {
            clear(pair.second);
        }
        delete node;
    }

    // problem01_lcp
    std::string Trie::lcp() const {
        TrieNode* current = root;
        std::string lcp;

        while(current->children.size() == 1) {
            auto child = current->children.begin();
            lcp += child->first;
            current = child->second;
        }
        return lcp;
    }

    // problem02_word_freq

    std::string Trie::most_common_word() const {
        std::string word, max_word;
        int max_count = 0;
        
        most_common_word_subtree(root, word, max_word, max_count);

        return max_word;
    }

    void Trie::most_common_word_subtree(TrieNode* subtree_root, std::string& word, std::string& max_word, int& max_count) const {
        if(subtree_root->wordend && 
            ( 
                subtree_root->count > max_count
                ||
                (
                    subtree_root->count == max_count
                    &&
                    word < max_word
                )
            )) {
            max_word = word;
            max_count = subtree_root->count;
        }

        for(auto& [ch, next] : subtree_root->children) {
            word.push_back(ch);
            most_common_word_subtree(next, word, max_word, max_count);
            word.pop_back();
        }
    }

    // problem03_autocomplete

    void Trie::autocomplete(const std::string& prefix) const {
        TrieNode* current = root;
        for (char ch : prefix) {
            if (!current->children.contains(ch)) {
                return;
            }
            current = current->children[ch];
        }

        std::string word = prefix;
        print_all_in_subtree(current, word);
    }

    void Trie::print_all_in_subtree(TrieNode* subtree_root, std::string& word) const {
        if(subtree_root->wordend) {
            std::cout << word << std::endl;
        }
        
        for(auto& [ch, next] : subtree_root->children) {
            word.push_back(ch);
            print_all_in_subtree(next, word);
            word.pop_back();
        }
    }

    // problem04_max_xor

    std::string Trie::find_max_xor(const std::string& num) const {
        std::string max_xor;
        int digit;
        TrieNode* current = root;
        for(char ch : num) {
            // digit = ch - '0';            
            if(current->children.contains('1'+'0'-ch)) {
                max_xor.push_back('1');
                current = current->children['1'+'0'-ch];
            } 
            else {
                max_xor.push_back('0');
                current = current->children[ch];
            }
        }
        return max_xor;   
    }
}