#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

/*
 * SUFFIX ARRAY - Lexicographically sorted array of all suffixes
 * 
 * Initialization:
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
 *                      Time: O(1)
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
 *   cout << sa.countDistinctSubstrings() << endl;
 *   vi matches = sa.find("ana");
 *   cout << sa.getLCP(1, 3) << endl;
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
    vi sa;
    vi pos;
    vi lcp;
    SparseTable<int, function<int(int, int)>> lcpST;
    
    SuffixArray(const string& str) : s(str), n(str.size()) {
        buildSuffixArray();
        buildLCP();
        
        function<int(int, int)> minFunc = [](int a, int b) { return min(a, b); };
        lcpST = SparseTable<int, function<int(int, int)>>(lcp, minFunc);
    }
    
    void buildSuffixArray() {
        sa.resize(n);
        pos.resize(n);
        vi temp(n), cnt(max(256, n), 0), temp_sa(n);
        
        for (int i = 0; i < n; i++) {
            sa[i] = i;
            pos[i] = s[i];
        }
        
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i++) {
                cnt[i] = 0;
            }
            
            for (int i = 0; i < n; i++) {
                int second = (i + k < n) ? pos[i + k] + 1 : 0;
                cnt[second]++;
            }
            
            for (int i = 1; i < max(256, n); i++) {
                cnt[i] += cnt[i - 1];
            }
            
            for (int i = n - 1; i >= 0; i--) {
                int second = (sa[i] + k < n) ? pos[sa[i] + k] + 1 : 0;
                temp_sa[--cnt[second]] = sa[i];
            }
            
            for (int i = 0; i < max(256, n); i++) {
                cnt[i] = 0;
            }
            
            for (int i = 0; i < n; i++) {
                cnt[pos[i]]++;
            }
            
            for (int i = 1; i < max(256, n); i++) {
                cnt[i] += cnt[i - 1];
            }
            
            for (int i = n - 1; i >= 0; i--) {
                sa[--cnt[pos[temp_sa[i]]]] = temp_sa[i];
            }
            
            temp[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                int prev_first = pos[sa[i - 1]];
                int prev_second = (sa[i - 1] + k < n) ? pos[sa[i - 1] + k] : -1;
                int cur_first = pos[sa[i]];
                int cur_second = (sa[i] + k < n) ? pos[sa[i] + k] : -1;
                
                if (prev_first == cur_first && prev_second == cur_second) {
                    temp[sa[i]] = temp[sa[i - 1]];
                } else {
                    temp[sa[i]] = temp[sa[i - 1]] + 1;
                }
            }
            pos = temp;
        }
    }
    
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
    
    int getLCP(int i, int j) {
        if (i == j) return n - i;
        
        int ri = pos[i];
        int rj = pos[j];
        
        if (ri > rj) swap(ri, rj);
        
        if (ri + 1 > rj) return 0;
        return lcpST.query(ri + 1, rj);
    }
    
    int compare(int i1, int l1, int i2, int l2) {
        if (i1 == i2 && l1 == l2) return 0;
        
        int commonLen = getLCP(i1, i2);
        int minLen = min(l1, l2);
        
        if (commonLen >= minLen) {
            if (l1 == l2) return 0;
            return (l1 < l2) ? -1 : 1;
        }
        
        int ri1 = pos[i1];
        int ri2 = pos[i2];
        
        return (ri1 < ri2) ? -1 : 1;
    }
    
    vi find(const string& pattern) {
        int m = pattern.size();
        vi result;
        
        if (m == 0 || m > n) return result;
        
        auto cmp = [&](int pos, const string& pat) -> int {
            int len = min(m, n - pos);
            for (int i = 0; i < len; i++) {
                if (s[pos + i] < pat[i]) return -1;
                if (s[pos + i] > pat[i]) return 1;
            }
            if (len < m) return -1;
            return 0;
        };
        
        int left = 0, right = n - 1;
        int leftBound = -1;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            int comp = cmp(sa[mid], pattern);
            
            if (comp >= 0) {
                if (comp == 0) {
                    leftBound = mid;
                }
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        if (leftBound == -1) return result;
        
        left = 0;
        right = n - 1;
        int rightBound = -1;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            int comp = cmp(sa[mid], pattern);
            
            if (comp == 0) {
                rightBound = mid;
                left = mid + 1;
            } else if (comp > 0) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        for (int i = leftBound; i <= rightBound; i++) {
            result.push_back(sa[i]);
        }
        
        sort(result.begin(), result.end());
        return result;
    }
    
    long long countDistinctSubstrings() {
        long long total = (long long)n * (n + 1) / 2;
        long long duplicates = 0;
        
        for (int i = 0; i < n; i++) {
            duplicates += lcp[i];
        }
        
        return total - duplicates;
    }
};
