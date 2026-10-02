#include "trie.hpp"

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
            if (!current->children.contains(ch)) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->wordend = true;
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
}