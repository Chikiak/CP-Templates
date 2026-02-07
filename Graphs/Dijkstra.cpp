#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;

const int INF = 1e18;

void dijkstra(int n, const vvpii& adj, int src, vi& dist, vi& parent) {
    dist.assign(n, INF);
    parent.assign(n, -1);
    
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

vi getPath(int dest, const vi& parent) {
    if (parent[dest] == -1 && dest != 0) return {};
    vi path;
    for (int v = dest; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}
