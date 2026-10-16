#include <iostream>
#include "../trie.hpp"

int main() {
    matf_daa::Trie* trie = new matf_daa::Trie();
    
    int n;
    std::cin >> n;
    std::string input;
    std::string max_xor, curr_xor;
    for(int i = 0; i < n; i++) {
        std::cin >> input;
        trie->insert(input);
        curr_xor = trie->find_max_xor(input);
        if(curr_xor > max_xor) max_xor = curr_xor;
    }

    std::cout << max_xor << std::endl;

    delete trie;

    return 0;
}