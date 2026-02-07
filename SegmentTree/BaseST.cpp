#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

struct SegmentTree {
    int n;
    vi tree;

    SegmentTree(int n) : n(n) {
        tree.assign(4 * n, 0);
    }

    void build(const vi& a, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, 2 * v, tl, tm);
            build(a, 2 * v + 1, tm + 1, tr);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            tree[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(2 * v, tl, tm, pos, new_val);
            else update(2 * v + 1, tm + 1, tr, pos, new_val);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return query(2 * v, tl, tm, l, min(r, tm))
             + query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
    }
    
    void build(const vi& a) { build(a, 1, 0, n - 1); }
    void update(int pos, int val) { update(1, 0, n - 1, pos, val); }
    int query(int l, int r) { return query(1, 0, n - 1, l, r); }
};