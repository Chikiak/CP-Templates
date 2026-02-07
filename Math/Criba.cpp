#include <bits/stdc++.h>

using namespace std;

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