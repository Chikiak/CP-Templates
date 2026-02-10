/**
 * SPARSE TABLE (Generic)
 * ----------------------
 * Static Range Queries in O(1) for IDEMPOTENT functions (min, max, gcd, bitwise AND/OR).
 * DO NOT USE for sum/xor (use Segment Tree).
 * 
 * USAGE:
 *   SparseTable<int> st(vec); // Defaults to min
 *   SparseTable<int> st(vec, [](int a, int b) { return gcd(a, b); });
 * 
 * COMPLEXITY:
 *   Build: O(N log N) time, O(N log N) space.
 *   Query: O(1) time.
 */

#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SparseTable {
    int n;
    vector<vector<T>> table;
    function<T(T, T)> func;

    SparseTable(const vector<T>& a, function<T(T, T)> f = [](T x, T y) { return min(x, y); }) 
        : n(a.size()), func(f) {
        if (n == 0) return;
        
        int maxLog = 32 - __builtin_clz(n);
        table.assign(maxLog, vector<T>(n));
        
        for (int i = 0; i < n; i++) table[0][i] = a[i];
        
        for (int j = 1; j < maxLog; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[j][i] = func(table[j - 1][i], 
                                   table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    
    T query(int l, int r) {
        int len = r - l + 1;
        int k = 31 - __builtin_clz(len);
        return func(table[k][l], table[k][r - (1 << k) + 1]);
    }
};
