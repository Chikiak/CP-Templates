#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef vector<int> vi;

/*
 * MODULAR ARITHMETIC - Essential modular operations
 * 
 * binpow:
 *   Arguments: a (base), b (exponent), mod (modulo)
 *   Result: Returns (a^b) % mod
 *   Time: O(log b)
 * 
 * extended_gcd:
 *   Arguments: a, b (integers), x, y (output coefficients by reference)
 *   Result: Returns gcd(a,b), stores x,y such that ax + by = gcd(a,b)
 *   Time: O(log min(a,b))
 * 
 * mod_inverse:
 *   Arguments: a (number), mod (modulo, must be coprime with a)
 *   Result: Returns a^(-1) mod 'mod', or -1 if inverse doesn't exist
 *   Time: O(log mod)
 * 
 * precompute_factorials:
 *   Arguments: n (max value), mod (modulo, must be prime)
 *   Result: Fills fact[] and inv_fact[] arrays for nCr computation
 *   Time: O(n)
 * 
 * nCr:
 *   Arguments: n, r (binomial parameters), mod (modulo)
 *   Result: Returns C(n,r) % mod (requires precompute_factorials first)
 *   Time: O(1)
 * 
 * crt:
 *   Arguments: remainders[], moduli[] (system of congruences)
 *   Result: Returns smallest x satisfying x ≡ remainders[i] (mod moduli[i])
 *           Returns -1 if no solution
 *   Time: O(n²)
 */

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
