#pragma once

#include<unordered_map>
#include<string>

namespace matf_daa {
    class Trie {
    public:
        Trie();
        ~Trie();

        void insert(const std::string& word);
        bool find(const std::string& word) const;
        
        // problem01_lcp 
        std::string lcp() const;

    private:
        struct TrieNode {
            bool wordend;
            std::unordered_map<char, TrieNode*> children;

            TrieNode();
        };

        TrieNode* root;

        void clear(TrieNode* node);
    };
}