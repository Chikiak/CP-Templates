#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef vector<int> vi;
typedef vector<vi> vvi;

const int INF = 1e18;

struct FloydWarshall {
    int n;
    vvi dist;
    
    FloydWarshall(int n) : n(n), dist(n, vi(n, INF)) {
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
    }
    
    void addEdge(int u, int v, int w) {
        dist[u][v] = min(dist[u][v], w);
    }
    
    void solve() {
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }
    
    bool hasNegativeCycle() {
        for (int i = 0; i < n; i++) {
            if (dist[i][i] < 0) {
                return true;
            }
        }
        return false;
    }
};
