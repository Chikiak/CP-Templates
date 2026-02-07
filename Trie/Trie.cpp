#include <bits/stdc++.h>
using namespace std;

/*
 * TRIE - Prefix tree for strings
 * 
 * Constructor:
 *   Trie() - Creates empty trie
 * 
 * Functions:
 *   insert(s)       - Insert string s into trie
 *   search(s)       - Returns true if exact string s exists in trie
 *   startsWith(prefix) - Returns true if any string starts with prefix
 * 
 * Time: O(|s|) per operation where |s| is string length
 */

struct Trie {
    struct Node {
        map<char, int> child;
        bool isEnd;
        Node() : isEnd(false) {}
    };
    
    vector<Node> nodes;
    
    Trie() {
        nodes.push_back(Node());
    }
    
    void insert(const string& s) {
        int cur = 0;
        for (char c : s) {
            if (!nodes[cur].child.count(c)) {
                nodes[cur].child[c] = nodes.size();
                nodes.push_back(Node());
            }
            cur = nodes[cur].child[c];
        }
        nodes[cur].isEnd = true;
    }
    
    bool search(const string& s) {
        int cur = 0;
        for (char c : s) {
            if (!nodes[cur].child.count(c)) {
                return false;
            }
            cur = nodes[cur].child[c];
        }
        return nodes[cur].isEnd;
    }
    
    bool startsWith(const string& prefix) {
        int cur = 0;
        for (char c : prefix) {
            if (!nodes[cur].child.count(c)) {
                return false;
            }
            cur = nodes[cur].child[c];
        }
        return true;
    }
};
