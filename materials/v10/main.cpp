#include<iostream>
#include<string>
#include<vector>

using namespace std;

int code(char c) {
    return c - 'a' + 1;
}

long long hash_lr(const string& s) {
    int p = 31;
    int m = 1e9 + 9;

    long long h = 0;
    for(int i = 0; i < s.size(); i++) {
        h = (h * p + code(s[i])) % m;
    }
}

long long hash_rl(const string& s) {
    int p = 31;
    int m = 1e9 + 9;

    long long h = 0;
    for(int i = s.size()-1; i >= 0; i--) {
        h = (h * p + code(s[i])) % m;
    }
}

unsigned mod_pow(unsigned a, unsigned n, unsigned m) {
    if (n == 0)
       return 1;
    if (n % 2 == 0)
        return mod_pow((a * a) % m, n / 2, m);
    else
        return (a * mod_pow(a, n-1, m)) % m;
}

vector<int> rabin_karp(const string& text, const string& sample) {
    int N = text.size();
    int M = sample.size();

    vector<int> positions;

    if(M > N)
        return positions;
    
    int p = 31;
    int m = 1e9 + 9;

    long long p_pow = mod_pow(p, M-1, m);

    long long hash_sample = 0;
    for(int i = 0; i < M; i++)
        hash_sample = (hash_sample * p + code(sample[i])) % m;

    long long hash_segment = 0;
    for(int i = 0; i < M; i++) 
        hash_segment = (hash_segment * p + code(text[i])) % m;

    for(int i = 0; i <= N - M; i++) {
        if(hash_segment == hash_sample) 
            if(sample == text.substr(i, M))
                positions.push_back(i);
            
        if(i < N - M)
            hash_segment = ((hash_segment - code(text[i])*p_pow + m) * p + code(text[i + M])) % m;
    }

    return positions;
}

vector<int> prefix_sufix(const string& s) {
    int m = s.size() + 1;
    vector<int> pi(m);

    int i = 0, j = -1;
    pi[i] = j;

    while(i + 1 < m) {
        while(j >= 0 && s[i] != s[j])
            j = pi[j];
        pi[++i] = ++j;
    }

    return pi;
}

vector<int> kmp(const string& text, const string& sample) {
    vector<int> pi = prefix_sufix(sample);
    vector<int> positions;

    int i = 0, j = 0;
    while(i + sample.size() <= text.size()) {
        while(j < sample.size()) {
            if(text[i+j] != sample[j])
                break;
            j++;
        }

        if(j == sample.size())
            positions.push_back(i);

        i += j - pi[j];
        j = max(pi[j], 0);
    }
}

int main() {

}