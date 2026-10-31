#include "trie.hpp"
#include <iostream>
#include <string>

namespace matf_daa {
    Trie::TrieNode::TrieNode() : wordend(false) {}

    Trie::Trie() {
        root = new TrieNode();
    }

    Trie::~Trie() {
        clear(root);
    }

    void Trie::insert(const std::string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->wordend = true;
    }

    bool Trie::find(const std::string& word) const {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
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
}