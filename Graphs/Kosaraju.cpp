#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

struct Kosaraju {
    int n;
    vvi adj, radj;
    vi order, comp;
    vector<bool> visited;
    int numSCC;
    
    Kosaraju(int n) : n(n), adj(n), radj(n), comp(n, -1), visited(n, false), numSCC(0) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
    
    void dfs1(int v) {
        visited[v] = true;
        for (int u : adj[v]) {
            if (!visited[u]) {
                dfs1(u);
            }
        }
        order.push_back(v);
    }
    
    void dfs2(int v, int c) {
        comp[v] = c;
        for (int u : radj[v]) {
            if (comp[u] == -1) {
                dfs2(u, c);
            }
        }
    }
    
    void findSCC() {
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs1(i);
            }
        }
        
        reverse(order.begin(), order.end());
        
        for (int v : order) {
            if (comp[v] == -1) {
                dfs2(v, numSCC);
                numSCC++;
            }
        }
    }
};
