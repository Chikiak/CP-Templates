// Modular Arithmetic Utilities for Competitive Programming
//
// This file contains essential modular arithmetic functions:
// - Binary exponentiation (binpow)
// - Extended Euclidean Algorithm (extended_gcd)
// - Modular inverse using Extended GCD
// - Factorial and inverse factorial precomputation for nCr
// - Chinese Remainder Theorem (CRT) for solving systems of congruences
//
// Usage:
// - binpow(a, b, mod): Computes (a^b) % mod in O(log b)
// - extended_gcd(a, b, x, y): Finds x, y such that ax + by = gcd(a, b)
// - mod_inverse(a, mod): Computes a^(-1) mod 'mod' (mod must be prime or coprime with a)
// - precompute_factorials(n, mod): Precomputes fact[] and inv_fact[] up to n
// - nCr(n, r, mod): Computes binomial coefficient C(n, r) % mod
// - crt(remainders, moduli): Solves system of congruences using CRT
//
// Time Complexity:
// - binpow: O(log b)
// - extended_gcd: O(log min(a, b))
// - mod_inverse: O(log mod)
// - precompute_factorials: O(n)
// - nCr: O(1) after precomputation
// - crt: O(n^2) where n is the number of congruences
//
// Space Complexity: O(n) for factorial arrays

#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef vector<int> vi;

// Binary exponentiation: computes (a^b) % mod
// a: base
// b: exponent
// mod: modulo value
// Returns: (a^b) % mod
// Time: O(log b)
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

// Extended Euclidean Algorithm
// Finds integers x, y such that a*x + b*y = gcd(a, b)
// a, b: input integers
// x, y: output coefficients (passed by reference)
// Returns: gcd(a, b)
// Time: O(log min(a, b))
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

// Modular inverse using Extended Euclidean Algorithm
// a: number to find inverse of
// mod: modulo value (should be coprime with a for inverse to exist)
// Returns: a^(-1) mod 'mod', or -1 if inverse doesn't exist
// Note: If mod is prime, you can also use binpow(a, mod-2, mod)
// Time: O(log mod)
int mod_inverse(int a, int mod) {
    int x, y;
    int g = extended_gcd(a, mod, x, y);
    if (g != 1) {
        return -1;  // Inverse doesn't exist
    }
    return (x % mod + mod) % mod;
}

// Factorial and inverse factorial arrays for nCr computation
const int MAXN = 1e6 + 5;
vi fact(MAXN);
vi inv_fact(MAXN);

// Precompute factorials and inverse factorials up to n
// n: maximum value to precompute up to
// mod: modulo value (must be prime for modular inverse)
// Modifies: fact[] and inv_fact[] arrays
// Time: O(n)
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

// Compute binomial coefficient C(n, r) % mod
// n, r: parameters for C(n, r)
// mod: modulo value
// Returns: C(n, r) % mod
// Note: Requires precompute_factorials to be called first
// Time: O(1) after precomputation
int nCr(int n, int r, int mod) {
    if (r < 0 || r > n) return 0;
    return (fact[n] * inv_fact[r] % mod) * inv_fact[n - r] % mod;
}

// Chinese Remainder Theorem
// Solves the system of congruences:
// x ≡ remainders[0] (mod moduli[0])
// x ≡ remainders[1] (mod moduli[1])
// ...
// x ≡ remainders[n-1] (mod moduli[n-1])
//
// remainders: array of remainders
// moduli: array of moduli (should be pairwise coprime)
// Returns: smallest non-negative solution x, or -1 if no solution exists
// Time: O(n^2) where n is the size of the arrays
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

// Example usage:
// int main() {
//     const int MOD = 1e9 + 7;
//     
//     // Binary exponentiation
//     cout << binpow(2, 10, MOD) << endl;  // 1024
//     
//     // Modular inverse
//     cout << mod_inverse(3, MOD) << endl;  // 333333336
//     
//     // nCr computation
//     precompute_factorials(100, MOD);
//     cout << nCr(10, 5, MOD) << endl;  // 252
//     
//     // Chinese Remainder Theorem
//     vi remainders = {2, 3, 2};
//     vi moduli = {3, 5, 7};
//     cout << crt(remainders, moduli) << endl;  // 23
// }
