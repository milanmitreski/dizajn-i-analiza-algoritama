#include<iostream>
#include<unordered_map>
#include<string>

struct TrieNode {
    public:
        TrieNode(): wordEnd(false) {}
        ~TrieNode() {
            for(auto child : children) {
                delete child.second;
            }
        }

        bool find(const std::string word) {
            return find(word, 0);
        }

        void insert(const std::string& word) {
            this->insert(word, 0);
        }

        void printAllWords() {
            std::string prefix;
            printAllWords(prefix);
        }

        void autocomplete(std::string prefix) {
            TrieNode* tmp = this;
            for(char c : prefix) {
                if(tmp->children.find(c) == tmp->children.end())
                    return;
                tmp = tmp->children[c];
            }
            tmp->printAllWords(prefix);
        }
    private:
        bool wordEnd;
        std::unordered_map<char, TrieNode*> children;

        bool find(const std::string& word, int pos) {
            if(word.size() == pos) {
                return this->wordEnd;
            }
            
            char key = word[pos];
            if(this->children.find(key) == this->children.end()) {
                return false;
            }
            return this->children[key]->find(word, pos+1);
        }

        void insert(const std::string& word, int pos) {
            if(word.size() == pos) {
                this->wordEnd = true;
                return;
            }

            char key = word[pos];
            if(this->children.find(key) == this->children.end()) {
                this->children[key] = new TrieNode();
            }
            this->children[key]->insert(word, pos+1);
        }

        void printAllWords(std::string& prefix) {
            if(this->wordEnd) {
                std::cout << prefix << std::endl;
            }

            for(auto child : children) {
                prefix.push_back(child.first);
                child.second->printAllWords(prefix);
                prefix.pop_back();
            }
        }
};

int main() {
    TrieNode* trie = new TrieNode();

    trie->insert("klima");
    trie->insert("klizanje");
    trie->insert("kriza");

    trie->printAllWords();

    std::string autocomplete;
    std::cin >> autocomplete;

    trie->autocomplete(autocomplete);
    
    delete trie;
}