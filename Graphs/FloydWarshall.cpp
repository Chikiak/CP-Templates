#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef vector<int> vi;
typedef vector<vi> vvi;

const int INF = 1e18;

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

bool hasNegativeCycle(int n, const vvi& dist) {
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            return true;
        }
    }
    return false;
}
