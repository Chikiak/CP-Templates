#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

/*
 * TARJAN'S ALGORITHM - Find Strongly Connected Components (single DFS)
 * 
 * Arguments:
 *   n        - Number of nodes in the graph (0-indexed)
 *   adj      - Adjacency list of directed graph
 *   comp     - Output: component ID for each node (will be modified)
 * 
 * Result: Returns number of SCCs. comp[i] contains SCC ID of node i (0 to numSCC-1)
 * 
 * Time: O(V + E)
 */

void tarjanDFS(int v, const vvi& adj, vi& low, vi& disc, vi& comp, 
               vector<bool>& onStack, stack<int>& st, int& timer, int& numSCC) {
    disc[v] = low[v] = timer++;
    st.push(v);
    onStack[v] = true;
    
    for (int u : adj[v]) {
        if (disc[u] == -1) {
            tarjanDFS(u, adj, low, disc, comp, onStack, st, timer, numSCC);
            low[v] = min(low[v], low[u]);
        } else if (onStack[u]) {
            low[v] = min(low[v], disc[u]);
        }
    }
    
    if (low[v] == disc[v]) {
        while (true) {
            int u = st.top();
            st.pop();
            onStack[u] = false;
            comp[u] = numSCC;
            if (u == v) break;
        }
        numSCC++;
    }
}

int tarjan(int n, const vvi& adj, vi& comp) {
    vi low(n), disc(n, -1);
    vector<bool> onStack(n, false);
    stack<int> st;
    int timer = 0, numSCC = 0;
    
    comp.assign(n, -1);
    
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            tarjanDFS(i, adj, low, disc, comp, onStack, st, timer, numSCC);
        }
    }
    
    return numSCC;
}
