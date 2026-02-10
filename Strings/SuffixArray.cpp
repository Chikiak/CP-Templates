/**
 * SUFFIX ARRAY + LCP + SPARSE TABLE
 * ---------------------------------
 * Algorithm:   Prefix Doubling (O(N log N)) + Kasai's Algorithm (O(N))
 * Description: Builds SA and LCP array. Sentinel '$' is appended to the END.
 *              Includes O(1) LCP queries via Sparse Table.
 * 
 * METHODS:
 *   query(i, j)            : LCP of suffixes at i and j. O(1)
 *   compare(i, l1, j, l2)  : Compare s[i..i+l1-1] vs s[j..j+l2-1]. Returns -1, 0, 1. O(1)
 *   find(P)                : Find all starting indices of pattern P. O(|P| log N)
 *   countDistinct()        : Count distinct substrings. O(N)
 * 
 * COMPLEXITY: Build O(N log N), Space O(N log N)
 */

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SparseTable {
    vector<vector<T>> table;
    int n;
    SparseTable() {}
    SparseTable(const vector<T>& a) : n(a.size()) {
        if (n == 0) return;
        int maxLog = 32 - __builtin_clz(n);
        table.assign(maxLog, vector<T>(n));
        for (int i = 0; i < n; i++) table[0][i] = a[i];
        for (int j = 1; j < maxLog; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                table[j][i] = min(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
    }
    T query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(table[k][l], table[k][r - (1 << k) + 1]);
    }
};

struct SuffixArray {
    string s;
    int n;
    vector<int> sa, rk, lcp;
    SparseTable<int> rmq;

    SuffixArray(string _s) : s(_s + '$'), n(s.size()) {
        buildSA();
        buildLCP();
        rmq = SparseTable<int>(lcp);
    }

    void buildSA() {
        sa.resize(n); rk.resize(n);
        vector<int> cnt(max(256, n)), p(n), cn(n);
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < 256; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) sa[--cnt[s[i]]] = i;
        rk[sa[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++) {
            if (s[sa[i]] != s[sa[i - 1]]) classes++;
            rk[sa[i]] = classes - 1;
        }
        for (int k = 0; (1 << k) < n; k++) {
            for (int i = 0; i < n; i++) {
                p[i] = sa[i] - (1 << k);
                if (p[i] < 0) p[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++) cnt[rk[p[i]]]++;
            for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) sa[--cnt[rk[p[i]]]] = p[i];
            cn[sa[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = {rk[sa[i]], rk[(sa[i] + (1 << k)) % n]};
                pair<int, int> prev = {rk[sa[i - 1]], rk[(sa[i - 1] + (1 << k)) % n]};
                if (cur != prev) classes++;
                cn[sa[i]] = classes - 1;
            }
            rk = cn;
            if (classes == n) break;
        }
    }

    void buildLCP() {
        lcp.assign(n, 0);
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (rk[i] == 0) continue;
            int j = sa[rk[i] - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[rk[i]] = k;
            if (k > 0) k--;
        }
    }

    int query(int i, int j) {
        if (i == j) return n - 1 - i;
        int ri = rk[i], rj = rk[j];
        if (ri > rj) swap(ri, rj);
        return rmq.query(ri + 1, rj);
    }

    int compare(int i, int len1, int j, int len2) {
        int common = query(i, j);
        int len = min(len1, len2);
        if (common >= len) return (len1 == len2) ? 0 : (len1 < len2 ? -1 : 1);
        return (s[i + common] < s[j + common]) ? -1 : 1;
    }

    vector<int> find(const string& pat) {
        int m = pat.size();
        int l = 0, r = n - 1, idx = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int res = s.compare(sa[mid], min(m, n - sa[mid]), pat);
            if (res == 0) { idx = mid; r = mid - 1; }
            else if (res < 0) l = mid + 1;
            else r = mid - 1;
        }
        vector<int> occ;
        if (idx != -1) {
            while (idx < n && s.compare(sa[idx], min(m, n - sa[idx]), pat) == 0)
                occ.push_back(sa[idx++]);
        }
        sort(occ.begin(), occ.end());
        return occ;
    }

    long long countDistinctSubstrings() {
        long long total = 0;
        for (int i = 1; i < n; i++) 
            total += (n - 1 - sa[i]) - lcp[i];
        return total;
    }
};
