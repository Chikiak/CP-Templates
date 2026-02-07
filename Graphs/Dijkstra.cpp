#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;

const int INF = 1e18;

struct Dijkstra {
    int n;
    vvpii adj;
    vi dist, parent;
    
    Dijkstra(int n) : n(n), adj(n), dist(n, INF), parent(n, -1) {}
    
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }
    
    void solve(int src) {
        priority_queue<pii, vpii, greater<pii>> pq;
        dist[src] = 0;
        pq.push({0, src});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }
    
    vi getPath(int dest) {
        if (dist[dest] == INF) return {};
        vi path;
        for (int v = dest; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};
