#include <bits/stdc++.h>

using namespace std;

/*
 * SIEVE OF ERATOSTHENES - Precompute prime numbers
 * 
 * precompute_primes:
 *   Arguments: None (uses global N)
 *   Result: Fills isPrime[] array where isPrime[i] = true if i is prime
 *   Time: O(N log log N)
 */

int N = 1e6+5;
vector<bool> isPrime(N);

void precompute_primes() {
    isPrime.assign(N, true);
    isPrime[0] = false; isPrime[1] = false;
    for (int i = 2; i < sqrt(N); i++) {
        if (!isPrime[i]) continue;
        for (int j = i*i; j < N; j += i) {
            isPrime[j] = false;
        }
    }
}