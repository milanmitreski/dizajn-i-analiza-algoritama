#include <iostream>
#include "../trie.hpp"

int main() {
    matf_daa::Trie* trie = new matf_daa::Trie();
    
    int n;
    std::cin >> n;
    std::string input;
    for(int i = 0; i < n; i++) {
        std::cin >> input;
        trie->insert(input);
    }

    std::cout << trie->lcp() << std::endl;

    delete trie;

    return 0;
}