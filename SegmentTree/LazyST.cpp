#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef vector<int> vi;

/*
 * LAZY SEGMENT TREE - Range updates and range queries
 * 
 * Constructor:
 *   LazySegmentTree(n) - Creates tree for n elements
 * 
 * Functions:
 *   build(a)          - Initialize tree with array a (0-indexed)
 *   update(l, r, add) - Add 'add' to all elements in range [l, r]
 *   query(l, r)       - Return sum of elements in range [l, r]
 * 
 * Time: O(log n) per operation
 */

struct LazySegmentTree {
    int n;
    vi tree, lazy;

    LazySegmentTree(int n) : n(n) {
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    void push(int v, int tl, int tr) {
        if (lazy[v] != 0) {
            tree[v] += lazy[v] * (tr - tl + 1);
            if (tl != tr) {
                lazy[2 * v] += lazy[v];
                lazy[2 * v + 1] += lazy[v];
            }
            lazy[v] = 0;
        }
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

    void update(int v, int tl, int tr, int l, int r, int add) {
        push(v, tl, tr);
        if (l > r) return;
        if (l == tl && r == tr) {
            lazy[v] += add;
            push(v, tl, tr);
        } else {
            int tm = (tl + tr) / 2;
            update(2 * v, tl, tm, l, min(r, tm), add);
            update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, add);
            push(2 * v, tl, tm);
            push(2 * v + 1, tm + 1, tr);
            tree[v] = tree[2 * v] + tree[2 * v + 1];
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        push(v, tl, tr);
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return query(2 * v, tl, tm, l, min(r, tm))
             + query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r);
    }

    void build(const vi& a) { build(a, 1, 0, n - 1); }
    void update(int l, int r, int add) { update(1, 0, n - 1, l, r, add); }
    int query(int l, int r) { return query(1, 0, n - 1, l, r); }
};
