#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;

const int INF = 1e18;

/*
 * DIJKSTRA'S ALGORITHM - Single source shortest path for non-negative weights
 * 
 * Arguments:
 *   n        - Number of nodes in the graph (0-indexed)
 *   adj      - Adjacency list where adj[u] = {{v, w}, ...} (edge u->v with weight w)
 *   src      - Source node
 *   dist     - Output: distances from src to all nodes (will be modified)
 *   parent   - Output: parent of each node in shortest path tree (will be modified)
 * 
 * Result: dist[i] contains shortest distance from src to i (INF if unreachable)
 *         parent[i] contains previous node in shortest path (-1 if none)
 * 
 * Time: O((V + E) log V)
 */
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

/*
 * GET PATH - Reconstruct shortest path from dijkstra result
 * 
 * Arguments:
 *   dest     - Destination node
 *   parent   - Parent array from dijkstra
 *   dist     - Distance array from dijkstra
 * 
 * Result: Returns vector of nodes in path from source to dest (empty if unreachable)
 */
vi getPath(int dest, const vi& parent, const vi& dist) {
    if (dist[dest] == INF) return {};
    vi path;
    for (int v = dest; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}
