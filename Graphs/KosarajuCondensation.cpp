#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

void dfs1_condensation(int v, const vvi& adj, vector<bool>& visited, vi& order) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs1_condensation(u, adj, visited, order);
        }
    }
    order.push_back(v);
}

void dfs2_condensation(int v, const vvi& radj, vi& comp, int c) {
    comp[v] = c;
    for (int u : radj[v]) {
        if (comp[u] == -1) {
            dfs2_condensation(u, radj, comp, c);
        }
    }
}

int kosarajuCondensation(int n, const vvi& adj, const vvi& radj, vi& comp, 
                          vvi& sccGraph, vi& sccSize) {
    vector<bool> visited(n, false);
    vi order;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs1_condensation(i, adj, visited, order);
        }
    }
    
    reverse(order.begin(), order.end());
    
    comp.assign(n, -1);
    int numSCC = 0;
    
    for (int v : order) {
        if (comp[v] == -1) {
            dfs2_condensation(v, radj, comp, numSCC);
            numSCC++;
        }
    }
    
    // Build condensation graph
    sccGraph.assign(numSCC, vi());
    sccSize.assign(numSCC, 0);
    
    for (int i = 0; i < n; i++) {
        sccSize[comp[i]]++;
    }
    
    set<pair<int, int>> edges;
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (comp[u] != comp[v]) {
                edges.insert({comp[u], comp[v]});
            }
        }
    }
    
    for (auto [u, v] : edges) {
        sccGraph[u].push_back(v);
    }
    
    return numSCC;
}
