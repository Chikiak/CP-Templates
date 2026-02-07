#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pii pair<int, int>
#define all(v) v.begin(), v.end()

struct RollbackDSU {
    vi parent, sz;
    struct Step { int u, v; };
    vector<Step> history;
    int numberOfSets;
    int R, C;

    RollbackDSU(int n) { init(n); }
    RollbackDSU(int r, int c) { R = r; C = c; init(r * c); }

    void init(int n) {
        parent.resize(n);
        iota(all(parent), 0);
        sz.assign(n, 1);
        numberOfSets = n;
    }

    int find(int a) {
        if (a == parent[a]) return a;
        return find(parent[a]);
    }

    bool merge(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        history.push_back({a, b});

        parent[b] = a;
        sz[a] += sz[b];
        numberOfSets--;
        return true;
    }

    void rollback() {
        if (history.empty()) return;
        Step last = history.back();
        history.pop_back();

        sz[last.u] -= sz[last.v];
        parent[last.v] = last.v;
        numberOfSets++;
    }
    // --------------------------------------------------
    int get_id(int r, int c) { return r * C + c; }
    int find(int r, int c) { return find(get_id(r, c)); }
    bool merge(int r1, int c1, int r2, int c2) {
        return merge(get_id(r1, c1), get_id(r2, c2));
    }
    // --------------------------------------------------
    int time() { return (int)history.size(); }
    void revert(int t) {
        while ((int)history.size() > t) rollback();
    }
};