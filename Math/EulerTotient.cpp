// Euler's Totient Function (phi function) for competitive programming
// phi(n) counts integers from 1 to n that are coprime with n
// Single value: O(sqrt(n)), Sieve for multiple: O(n log log n)
// Used in modular arithmetic, Euler's theorem, and number theory problems

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define forn(i,s,n) for(int i = (int)s; i < (int) n; i++)
typedef vector<int> vi;

int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

vi phi_sieve(int n) {
    vi phi(n + 1);
    forn(i, 0, n + 1) phi[i] = i;
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    return phi;
}
