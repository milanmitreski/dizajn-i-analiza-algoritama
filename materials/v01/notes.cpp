#include<iostream>
#include<unordered_map>

using namespace std;

class Node {
public:
    Node(): isWordEnd(false) {}
    ~Node() {
        for(auto child : children) {
            delete child.second;
        }
    }

    bool find(const string& word) {
        return find(word, 0);
    }

    void insert(const string& word) {
        insert(word, 0);
    }

    void autocomplete(const string& prefix) {
        Node* current = this;
        string prefix_copy = prefix;

        for(char c : prefix) {
            if(current->children.find(c) == current->children.end()) {
                return;
            }
            current = current->children[c];
        }

        current->printAllWords(prefix_copy);
    }
private:
    bool isWordEnd;
    unordered_map<char, Node*> children;

    bool find(const string& word, int i) {
        if(i == word.size()) {
            return isWordEnd;
        }

        char key = word[i];
        if(this->children.find(key) == this->children.end()) {
            return false;
        }
        return this->children[key]->find(word, i+1);
    }

    void insert(const string& word, int i) {
        if(i == word.size()) {
            isWordEnd = true;
            return;
        }

        char key = word[i];
        if(this->children.find(key) == this->children.end()) {
            this->children[key] = new Node();
        }
        this->children[key]->insert(word, i+1);
    }

    void printAllWords(string& prefix) {
        if(this->isWordEnd) {
            cout << prefix << endl;
        }

        for(auto child : children) {
            prefix.push_back(child.first);
            child.second->printAllWords(prefix);
            prefix.pop_back();
        }
    }
};

int main() {
    Node* trie = new Node();

    trie->insert("klima");
    trie->insert("klizanje");

    cout << trie->find("klima") << endl;
    cout << trie->find("kriza") << endl;

    trie->insert("kriza");

    cout << trie->find("kriza") << endl;

    string autocomplete;
    cout << "Unesite prefiks: ";
    cin >> autocomplete;

    trie->autocomplete(autocomplete);
    
    delete trie;
}