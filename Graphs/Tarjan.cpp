#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

struct Tarjan {
    int n;
    vvi adj;
    vi low, disc, comp;
    vector<bool> onStack;
    stack<int> st;
    int timer, numSCC;
    
    Tarjan(int n) : n(n), adj(n), low(n), disc(n, -1), comp(n, -1), 
                     onStack(n, false), timer(0), numSCC(0) {}
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    void dfs(int v) {
        disc[v] = low[v] = timer++;
        st.push(v);
        onStack[v] = true;
        
        for (int u : adj[v]) {
            if (disc[u] == -1) {
                dfs(u);
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
    
    void findSCC() {
        for (int i = 0; i < n; i++) {
            if (disc[i] == -1) {
                dfs(i);
            }
        }
    }
};
