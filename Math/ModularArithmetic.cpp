// Modular arithmetic operations for competitive programming
// Provides: modular exponentiation, extended GCD, modular inverse
// Combinatorics: precomputed factorials and nCr with modular inverse
// Chinese Remainder Theorem for system of linear congruences
// Time: O(log n) for binpow and modInverse, O(n) for factorial precomputation, O(n log n) for CRT

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define forn(i,s,n) for(int i = (int)s; i < (int) n; i++)
typedef vector<int> vi;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;

vi fact(MAXN), inv_fact(MAXN);

int binpow(int a, int b, int m = MOD) {
    int res = 1;
    a %= m;
    while (b > 0) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

int extended_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int modInverse(int a, int m = MOD) {
    return binpow(a, m - 2, m);
}

void precompute_factorials(int n) {
    fact[0] = 1;
    forn(i, 1, n + 1) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    inv_fact[n] = modInverse(fact[n], MOD);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;
    }
}

int nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return (fact[n] * inv_fact[r] % MOD) * inv_fact[n - r] % MOD;
}

int crt(vi &a, vi &m) {
    int n = a.size();
    int M = 1;
    forn(i, 0, n) M *= m[i];
    int result = 0;
    forn(i, 0, n) {
        int Mi = M / m[i];
        int x, y;
        extended_gcd(Mi, m[i], x, y);
        result = (result + a[i] * Mi % M * x % M) % M;
    }
    return (result % M + M) % M;
}
