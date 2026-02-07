// Matrix multiplication and exponentiation for competitive programming
// Provides matrix multiplication and binary exponentiation for vvi matrices
// Useful for solving linear recurrences and graph problems
// Time: O(n^3) for multiplication, O(n^3 * log k) for exponentiation

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define forn(i,s,n) for(int i = (int)s; i < (int) n; i++)
typedef vector<int> vi;
typedef vector<vi> vvi;

const int MOD = 1e9 + 7;

vvi matmul(vvi &A, vvi &B) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();
    vvi C(n, vi(m, 0));
    forn(i, 0, n) {
        forn(j, 0, m) {
            forn(k, 0, p) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

vvi matpow(vvi &A, int k) {
    int n = A.size();
    vvi res(n, vi(n, 0));
    forn(i, 0, n) res[i][i] = 1;
    vvi base = A;
    while (k > 0) {
        if (k & 1) res = matmul(res, base);
        base = matmul(base, base);
        k >>= 1;
    }
    return res;
}
