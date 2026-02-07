// Sieve of Eratosthenes (Criba de Eratóstenes) for competitive programming
// Efficiently finds all prime numbers up to N in O(N log log N) time
// isPrime[i] indicates whether i is prime (true) or composite (false)
// Use precompute_primes() to initialize, then query isPrime array

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define forn(i,s,n) for(int i = (int)s; i < (int) n; i++)
typedef vector<bool> vb;

int N = 1e6 + 5;
vb isPrime(N);

void precompute_primes() {
    isPrime.assign(N, true);
    isPrime[0] = false; isPrime[1] = false;
    forn(i, 2, (int)sqrt(N) + 1) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j < N; j += i) {
            isPrime[j] = false;
        }
    }
}
