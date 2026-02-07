#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pii pair<int, int>
#define all(v) v.begin(), v.end()

struct DSU {
    vi parent, sz;
    int numberOfSets;
    int R, C;

    DSU(int n) {
        init(n);
    }

    DSU(int r, int c) {
        R = r; C = c;
        init(r * c);
    }

    void init(int n) {
        parent.resize(n);
        iota(all(parent), 0);
        sz.assign(n, 1);
        numberOfSets = n;
    }

    // -------------------------------------------
    int get_id(int r, int c) {
        return r * C + c;
    }
    int find(int r, int c) {
        return find(get_id(r, c));
    }
    bool merge(int r1, int c1, int r2, int c2) {
        return merge(get_id(r1, c1), get_id(r2, c2));
    }
    // -------------------------------------------
    int find(int a) {
        if (a == parent[a]) return a;
        return parent[a] = find(parent[a]); // Path compression
    }
    bool merge(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        numberOfSets--;
        return true;
    }
    // -------------------------------------------
    bool sameSet(int a, int b) {
        return find(a) == find(b);
    }
    int getSetSize(int a) {
        return sz[find(a)];
    }
};