#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

void dfs1(int v, const vvi& adj, vector<bool>& visited, vi& order) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs1(u, adj, visited, order);
        }
    }
    order.push_back(v);
}

void dfs2(int v, const vvi& radj, vi& comp, int c) {
    comp[v] = c;
    for (int u : radj[v]) {
        if (comp[u] == -1) {
            dfs2(u, radj, comp, c);
        }
    }
}

int kosaraju(int n, const vvi& adj, const vvi& radj, vi& comp) {
    vector<bool> visited(n, false);
    vi order;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs1(i, adj, visited, order);
        }
    }
    
    reverse(order.begin(), order.end());
    
    comp.assign(n, -1);
    int numSCC = 0;
    
    for (int v : order) {
        if (comp[v] == -1) {
            dfs2(v, radj, comp, numSCC);
            numSCC++;
        }
    }
    
    return numSCC;
}
