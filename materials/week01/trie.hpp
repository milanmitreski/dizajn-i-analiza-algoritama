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

        // problem02_word_freq
        std::string most_common_word() const;

        // problem03_autocomplete
        void autocomplete(const std::string& prefix) const;

        // problem04_max_xor 
        std::string find_max_xor(const std::string& num) const;

    private:
        struct TrieNode {
            bool wordend;
            std::unordered_map<char, TrieNode*> children;
            
            // problem02_word_freq
            int count;

            TrieNode();
        };

        TrieNode* root;

        void clear(TrieNode* node);
        
        // problem02_word_freq
        void most_common_word_subtree(TrieNode* subtree_root, std::string& word, std::string& max_word, int& max_count) const;
    
        // problem03_autocomplete
        void print_all_in_subtree(TrieNode* subtree_root, std::string& word) const;
    };
}