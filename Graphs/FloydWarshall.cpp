#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef vector<int> vi;
typedef vector<vi> vvi;

const int INF = 1e18;

/*
 * FLOYD-WARSHALL ALGORITHM - All pairs shortest paths
 * 
 * Arguments:
 *   n        - Number of nodes in the graph (0-indexed)
 *   dist     - Distance matrix where dist[i][j] = weight of edge i->j
 *              Initialize: dist[i][i] = 0, dist[i][j] = INF if no edge
 *              (will be modified to contain shortest paths)
 * 
 * Result: dist[i][j] contains shortest distance from i to j
 * 
 * Time: O(V^3)
 */
void floydWarshall(int n, vvi& dist) {
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

/*
 * CHECK NEGATIVE CYCLE - Detect if graph has negative cycle
 * 
 * Arguments:
 *   n        - Number of nodes
 *   dist     - Distance matrix after running floydWarshall
 * 
 * Result: Returns true if there exists a negative cycle
 */
bool hasNegativeCycle(int n, const vvi& dist) {
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            return true;
        }
    }
    return false;
}
