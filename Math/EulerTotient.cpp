// Euler's Totient Function (φ function) for Competitive Programming
//
// Euler's Totient function φ(n) counts the number of integers from 1 to n
// that are coprime with n (i.e., gcd(k, n) = 1 for 1 ≤ k ≤ n)
//
// Properties:
// - φ(1) = 1
// - φ(p) = p - 1 for prime p
// - φ(p^k) = p^(k-1) * (p - 1) for prime p
// - φ(m * n) = φ(m) * φ(n) if gcd(m, n) = 1 (multiplicative function)
// - φ(n) = n * ∏(1 - 1/p) for all prime divisors p of n
//
// This file contains:
// - phi(n): Computes φ(n) for a single integer
// - sieve_phi(N): Computes φ(i) for all i from 1 to N using sieve
//
// Usage:
// - phi(n): Returns φ(n) in O(sqrt(n))
// - sieve_phi(N): Precomputes phi[] array for all i ≤ N in O(N log log N)
//
// Time Complexity:
// - phi(n): O(sqrt(n))
// - sieve_phi(N): O(N log log N)
//
// Space Complexity:
// - phi(n): O(1)
// - sieve_phi(N): O(N)

#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef vector<int> vi;

// Compute Euler's Totient function φ(n) for a single number
// n: input integer
// Returns: φ(n) = count of integers from 1 to n coprime with n
// Time: O(sqrt(n))
int phi(int n) {
    int result = n;
    
    // Iterate through all potential prime factors
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            // Remove all factors of p
            while (n % p == 0) {
                n /= p;
            }
            // Apply formula: φ(n) = n * (1 - 1/p)
            result -= result / p;
        }
    }
    
    // If n > 1, then it's a prime factor
    if (n > 1) {
        result -= result / n;
    }
    
    return result;
}

// Sieve-based computation of Euler's Totient for all numbers up to N
// N: maximum value to compute phi for
// Returns: vector phi where phi[i] = φ(i) for all i from 0 to N
// Time: O(N log log N)
// Space: O(N)
vi sieve_phi(int N) {
    vi phi(N + 1);
    
    // Initialize phi[i] = i
    for (int i = 0; i <= N; i++) {
        phi[i] = i;
    }
    
    // Sieve to compute phi using the formula
    for (int p = 2; p <= N; p++) {
        if (phi[p] == p) {  // p is prime
            // For all multiples of p, apply φ(n) = n * (1 - 1/p)
            for (int j = p; j <= N; j += p) {
                phi[j] -= phi[j] / p;
            }
        }
    }
    
    return phi;
}

// Alternative sieve implementation that tracks smallest prime factor
// This can be useful if you need both phi and prime factorization
// N: maximum value to compute phi for
// Returns: vector phi where phi[i] = φ(i) for all i from 0 to N
// Time: O(N log log N)
// Space: O(N)
vi sieve_phi_spf(int N) {
    vi phi(N + 1);
    vi spf(N + 1);  // smallest prime factor
    
    // Initialize
    for (int i = 0; i <= N; i++) {
        phi[i] = i;
        spf[i] = i;
    }
    
    // Sieve
    for (int p = 2; p <= N; p++) {
        if (spf[p] == p) {  // p is prime
            for (int j = p; j <= N; j += p) {
                if (spf[j] == j) {
                    spf[j] = p;
                }
                phi[j] -= phi[j] / p;
            }
        }
    }
    
    return phi;
}

// Example usage:
// int main() {
//     // Compute φ(n) for a single number
//     cout << phi(12) << endl;  // 4 (numbers 1, 5, 7, 11 are coprime with 12)
//     cout << phi(9) << endl;   // 6 (numbers 1, 2, 4, 5, 7, 8 are coprime with 9)
//     
//     // Compute φ for all numbers up to N
//     int N = 100;
//     vi phi_values = sieve_phi(N);
//     for (int i = 1; i <= 10; i++) {
//         cout << "phi(" << i << ") = " << phi_values[i] << endl;
//     }
//     
//     // phi(1) = 1
//     // phi(2) = 1
//     // phi(3) = 2
//     // phi(4) = 2
//     // phi(5) = 4
//     // phi(6) = 2
//     // phi(7) = 6
//     // phi(8) = 4
//     // phi(9) = 6
//     // phi(10) = 4
// }
