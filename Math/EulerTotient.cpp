#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef vector<int> vi;

int phi(int n) {
    int result = n;
    
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            result -= result / p;
        }
    }
    
    if (n > 1) {
        result -= result / n;
    }
    
    return result;
}

vi sieve_phi(int N) {
    vi phi(N + 1);
    
    for (int i = 0; i <= N; i++) {
        phi[i] = i;
    }
    
    for (int p = 2; p <= N; p++) {
        if (phi[p] == p) {
            for (int j = p; j <= N; j += p) {
                phi[j] -= phi[j] / p;
            }
        }
    }
    
    return phi;
}

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
