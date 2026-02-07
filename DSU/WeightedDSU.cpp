#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pii pair<int, int>
#define all(v) v.begin(), v.end()

struct WeightedDSU {
    vi parent, sz, dist;
    int numberOfSets;
    int R, C;

    WeightedDSU(int n) { init(n); }
    WeightedDSU(int r, int c) { R = r; C = c; init(r * c); }

    void init(int n) {
        parent.resize(n);
        iota(all(parent), 0);
        sz.assign(n, 1);
        dist.assign(n, 0);
        numberOfSets = n;
    }

    int find(int a) {
        if (a == parent[a]) return a;
        int root = find(parent[a]);
        dist[a] += dist[parent[a]];
        return parent[a] = root;
    }

    bool merge(int a, int b, int w) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;

        if (sz[ra] < sz[rb]) {
            swap(ra, rb);
            swap(a, b);
            w = -w;
        }

        parent[rb] = ra;
        dist[rb] = dist[a] - dist[b] - w;
        sz[ra] += sz[rb];
        numberOfSets--;
        return true;
    }

    int get_dist(int a, int b) {
        if (find(a) != find(b)) return 1e18;
        return abs(dist[a] - dist[b]);
    }

    int get_id(int r, int c) { return r * C + c; }
    int find(int r, int c) { return find(get_id(r, c)); }
    bool merge(int r1, int c1, int r2, int c2, int w) {
        return merge(get_id(r1, c1), get_id(r2, c2), w);
    }
    int get_dist(int r1, int c1, int r2, int c2) {
        return get_dist(get_id(r1, c1), get_id(r2, c2));
    }
};