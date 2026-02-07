#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef vector<int> vi;

int binpow(int a, int b, int mod) {
    int result = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return result;
}

int extended_gcd(int a, int b, int& x, int& y) {
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

int mod_inverse(int a, int mod) {
    int x, y;
    int g = extended_gcd(a, mod, x, y);
    if (g != 1) {
        return -1;  // Inverse doesn't exist
    }
    return (x % mod + mod) % mod;
}

const int MAXN = 1e6 + 5;
vi fact(MAXN);
vi inv_fact(MAXN);

void precompute_factorials(int n, int mod) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    
    inv_fact[n] = binpow(fact[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
    }
}

int nCr(int n, int r, int mod) {
    if (r < 0 || r > n) return 0;
    return (fact[n] * inv_fact[r] % mod) * inv_fact[n - r] % mod;
}

int crt(const vi& remainders, const vi& moduli) {
    int n = remainders.size();
    if (n == 0) return 0;
    
    int M = 1;
    for (int i = 0; i < n; i++) {
        M *= moduli[i];
    }
    
    int result = 0;
    for (int i = 0; i < n; i++) {
        int Mi = M / moduli[i];
        int yi = mod_inverse(Mi, moduli[i]);
        if (yi == -1) return -1;  // Moduli are not pairwise coprime
        result = (result + remainders[i] * Mi % M * yi % M) % M;
    }
    
    return (result % M + M) % M;
}
