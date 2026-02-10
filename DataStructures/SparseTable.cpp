#include <bits/stdc++.h>
using namespace std;

/*
 * SPARSE TABLE - Range query data structure with O(1) query time
 * 
 * Initialization:
 *   SparseTable<T, F>(a, func) - Creates sparse table from array a with binary function func
 *   
 * Arguments:
 *   a    - Input array/vector of elements
 *   func - Binary function for combining values (e.g., min, max, gcd)
 *          Must be associative and idempotent (i.e., f(x,x) = x)
 * 
 * Functions:
 *   query(l, r) - Returns result of func over range [l, r] (0-indexed, inclusive)
 * 
 * Time Complexity:
 *   Construction: O(N log N) where N = array size
 *   Query: O(1)
 * 
 * Space: O(N log N)
 * 
 * Note: Works best with idempotent operations like min, max, gcd
 *       For non-idempotent operations (sum, xor), use Segment Tree instead
 * 
 * Example usage:
 *   vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
 *   
 *   auto minFunc = [](int x, int y) { return min(x, y); };
 *   SparseTable<int, decltype(minFunc)> st(a, minFunc);
 *   cout << st.query(2, 5) << endl;
 *   
 *   auto maxFunc = [](int x, int y) { return max(x, y); };
 *   SparseTable<int, decltype(maxFunc)> st2(a, maxFunc);
 *   cout << st2.query(0, 3) << endl;
 */

template<typename T, typename F>
struct SparseTable {
    int n;
    vector<vector<T>> table;
    vector<int> logTable;
    F func;
    
    SparseTable(const vector<T>& a, F f) : n(a.size()), func(f) {
        if (n == 0) return;
        
        logTable.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i / 2] + 1;
        }
        
        int maxLog = logTable[n] + 1;
        table.assign(maxLog, vector<T>(n));
        
        for (int i = 0; i < n; i++) {
            table[0][i] = a[i];
        }
        
        for (int j = 1; j < maxLog; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                table[j][i] = func(table[j - 1][i], 
                                   table[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    
    T query(int l, int r) {
        int len = r - l + 1;
        int k = logTable[len];
        return func(table[k][l], table[k][r - (1 << k) + 1]);
    }
};
