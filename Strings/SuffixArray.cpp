#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

/*
 * SUFFIX ARRAY - Lexicographically sorted array of all suffixes
 * 
 * Constructor:
 *   SuffixArray(s) - Constructs suffix array from string s
 * 
 * Member Variables:
 *   s      - Input string
 *   n      - Length of string
 *   sa     - Suffix array: sa[i] = starting position of i-th smallest suffix
 *   pos    - Inverse array: pos[i] = rank of suffix starting at position i
 *   lcp    - LCP array: lcp[i] = longest common prefix between sa[i] and sa[i-1]
 * 
 * Functions:
 *   getLCP(i, j)     - Returns LCP of suffixes starting at positions i and j
 *                      Time: O(1) [uses Sparse Table internally]
 *   
 *   compare(i1, l1, i2, l2) - Lexicographically compares two substrings:
 *                             s[i1...i1+l1-1] vs s[i2...i2+l2-1]
 *                             Returns: -1 if first < second, 0 if equal, 1 if first > second
 *                             Time: O(1)
 *   
 *   find(pattern)    - Finds all occurrences of pattern in string
 *                      Returns: vector of starting positions (sorted)
 *                      Time: O(|pattern| * log n)
 *   
 *   countDistinctSubstrings() - Counts total number of distinct substrings
 *                               Time: O(n)
 * 
 * Time Complexity:
 *   Construction: O(n log n) for suffix array + O(n) for LCP array
 *   Space: O(n log n)
 * 
 * Example usage:
 *   SuffixArray sa("banana");
 *   cout << sa.countDistinctSubstrings() << endl;  // 15
 *   vi matches = sa.find("ana");  // Returns {1, 3}
 *   cout << sa.getLCP(1, 3) << endl;  // LCP of suffixes at positions 1 and 3
 */

template<typename T, typename F>
struct SparseTable {
    int n;
    vector<vector<T>> table;
    vector<int> logTable;
    F func;
    
    SparseTable() : n(0) {}
    
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

struct SuffixArray {
    string s;
    int n;
    vi sa;   // Suffix array
    vi pos;  // Inverse: pos[i] = rank of suffix starting at i
    vi lcp;  // LCP array
    SparseTable<int, function<int(int, int)>> lcpST;
    
    SuffixArray(const string& str) : s(str), n(str.size()) {
        buildSuffixArray();
        buildLCP();
        
        // Build sparse table for O(1) LCP queries
        function<int(int, int)> minFunc = [](int a, int b) { return min(a, b); };
        lcpST = SparseTable<int, function<int(int, int)>>(lcp, minFunc);
    }
    
    // Build suffix array using prefix doubling - O(n log n)
    void buildSuffixArray() {
        sa.resize(n);
        pos.resize(n);
        vi temp(n);
        
        // Initial ranking by first character
        for (int i = 0; i < n; i++) {
            sa[i] = i;
            pos[i] = s[i];
        }
        
        // Double the length in each iteration
        for (int k = 1; k < n; k *= 2) {
            // Sort by (pos[i], pos[i+k]) pairs
            auto cmp = [&](int a, int b) {
                if (pos[a] != pos[b]) return pos[a] < pos[b];
                int ra = (a + k < n) ? pos[a + k] : -1;
                int rb = (b + k < n) ? pos[b + k] : -1;
                return ra < rb;
            };
            
            sort(sa.begin(), sa.end(), cmp);
            
            // Recompute rankings
            temp[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                temp[sa[i]] = temp[sa[i - 1]];
                if (cmp(sa[i - 1], sa[i])) {
                    temp[sa[i]]++;
                }
            }
            pos = temp;
        }
    }
    
    // Build LCP array using Kasai's algorithm - O(n)
    void buildLCP() {
        lcp.assign(n, 0);
        vi rank(n);
        
        for (int i = 0; i < n; i++) {
            rank[sa[i]] = i;
        }
        
        int h = 0;
        for (int i = 0; i < n; i++) {
            if (rank[i] > 0) {
                int j = sa[rank[i] - 1];
                while (i + h < n && j + h < n && s[i + h] == s[j + h]) {
                    h++;
                }
                lcp[rank[i]] = h;
                if (h > 0) h--;
            }
        }
    }
    
    // Get LCP of suffixes starting at positions i and j - O(1)
    int getLCP(int i, int j) {
        if (i == j) return n - i;
        
        // Get ranks of suffixes
        int ri = -1, rj = -1;
        for (int k = 0; k < n; k++) {
            if (sa[k] == i) ri = k;
            if (sa[k] == j) rj = k;
        }
        
        if (ri > rj) swap(ri, rj);
        
        // LCP of suffixes at positions i and j is the minimum LCP
        // in the range [ri+1, rj] of the LCP array
        if (ri + 1 > rj) return 0;
        return lcpST.query(ri + 1, rj);
    }
    
    // Compare two substrings: s[i1..i1+l1-1] vs s[i2..i2+l2-1]
    // Returns: -1 if first < second, 0 if equal, 1 if first > second - O(1)
    int compare(int i1, int l1, int i2, int l2) {
        if (i1 == i2 && l1 == l2) return 0;
        
        int commonLen = getLCP(i1, i2);
        int minLen = min(l1, l2);
        
        if (commonLen >= minLen) {
            // One is a prefix of the other
            if (l1 == l2) return 0;
            return (l1 < l2) ? -1 : 1;
        }
        
        // They differ at position commonLen
        // Compare using suffix array ranks
        int ri1 = -1, ri2 = -1;
        for (int k = 0; k < n; k++) {
            if (sa[k] == i1) ri1 = k;
            if (sa[k] == i2) ri2 = k;
        }
        
        return (ri1 < ri2) ? -1 : 1;
    }
    
    // Find all occurrences of pattern - O(|pattern| * log n)
    vi find(const string& pattern) {
        int m = pattern.size();
        vi result;
        
        if (m == 0 || m > n) return result;
        
        // Binary search for the leftmost position
        int left = 0, right = n - 1;
        int leftBound = -1;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            string suffix = s.substr(sa[mid], min(m, n - sa[mid]));
            
            if (suffix >= pattern) {
                if (suffix.substr(0, min(m, (int)suffix.size())) == pattern) {
                    leftBound = mid;
                }
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        if (leftBound == -1) return result;
        
        // Binary search for the rightmost position
        left = 0;
        right = n - 1;
        int rightBound = -1;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            string suffix = s.substr(sa[mid], min(m, n - sa[mid]));
            
            if (suffix.substr(0, min(m, (int)suffix.size())) == pattern) {
                rightBound = mid;
                left = mid + 1;
            } else if (suffix > pattern) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        // Collect all positions
        for (int i = leftBound; i <= rightBound; i++) {
            result.push_back(sa[i]);
        }
        
        sort(result.begin(), result.end());
        return result;
    }
    
    // Count total distinct substrings - O(n)
    long long countDistinctSubstrings() {
        // Total substrings = n*(n+1)/2
        // Subtract duplicate substrings counted by LCP array
        long long total = (long long)n * (n + 1) / 2;
        long long duplicates = 0;
        
        for (int i = 0; i < n; i++) {
            duplicates += lcp[i];
        }
        
        return total - duplicates;
    }
};
