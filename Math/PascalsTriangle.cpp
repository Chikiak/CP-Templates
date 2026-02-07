// Pascal's Triangle for computing binomial coefficients
// Precomputes C[n][k] = nCr values up to C[34][34] using dynamic programming
// Time: O(n^2) for precomputation, O(1) for queries
// Use precomputePascalsTriangle() to initialize, then access C[n][k] directly

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define forn(i,s,n) for(int i = (int)s; i < (int) n; i++)

int C[35][35];

void precomputePascalsTriangle() {
    forn(i, 0, 32) {
        forn(j, 0, 32) {
            C[i][j] = 0;
        }
    }
    
    forn(i, 0, 35) {
        C[i][0] = 1;
        forn(j, 1, i + 1) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}