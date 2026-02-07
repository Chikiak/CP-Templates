#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
 * BINARY TRIE - Trie for binary representations (useful for XOR problems)
 * 
 * Constructor:
 *   BinaryTrie(maxlog) - Creates trie for numbers with up to maxlog bits (default 30)
 * 
 * Functions:
 *   insert(x)  - Insert number x into trie
 *   remove(x)  - Remove number x from trie (decrements count)
 *   maxXor(x)  - Returns maximum XOR of x with any number in trie
 * 
 * Time: O(log max_value) per operation
 */

struct BinaryTrie {
    struct Node {
        int child[2];
        int cnt;
        Node() : cnt(0) {
            child[0] = child[1] = -1;
        }
    };
    
    vector<Node> nodes;
    int MAXLOG;
    
    BinaryTrie(int maxlog = 30) : MAXLOG(maxlog) {
        nodes.push_back(Node());
    }
    
    void insert(int x) {
        int cur = 0;
        for (int i = MAXLOG; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (nodes[cur].child[bit] == -1) {
                nodes[cur].child[bit] = nodes.size();
                nodes.push_back(Node());
            }
            cur = nodes[cur].child[bit];
            nodes[cur].cnt++;
        }
    }
    
    void remove(int x) {
        int cur = 0;
        for (int i = MAXLOG; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (nodes[cur].child[bit] == -1) return;
            cur = nodes[cur].child[bit];
            nodes[cur].cnt--;
        }
    }
    
    int maxXor(int x) {
        int cur = 0;
        int result = 0;
        for (int i = MAXLOG; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int want = 1 - bit;
            if (nodes[cur].child[want] != -1 && nodes[nodes[cur].child[want]].cnt > 0) {
                result |= (1LL << i);
                cur = nodes[cur].child[want];
            } else if (nodes[cur].child[bit] != -1) {
                cur = nodes[cur].child[bit];
            } else {
                return result;
            }
        }
        return result;
    }
};
