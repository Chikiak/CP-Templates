#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef vector<int> vi;
typedef vector<vi> vvi;

/*
 * MATRIX UTILITIES - Matrix operations for competitive programming
 * 
 * multiply:
 *   Arguments: A (n×m matrix), B (m×p matrix)
 *   Result: Returns C = A×B (n×p matrix)
 * 
 * multiply_mod:
 *   Arguments: A (n×m matrix), B (m×p matrix), mod (modulo value)
 *   Result: Returns (A×B) mod 'mod'
 * 
 * matpow:
 *   Arguments: A (square n×n matrix), exp (exponent), mod (modulo value)
 *   Result: Returns A^exp mod 'mod' using binary exponentiation
 * 
 * Time: O(n³) for multiply, O(n³ log exp) for matpow
 */

vvi multiply(const vvi& A, const vvi& B) {
    int n = A.size();
    int m = B.size();
    int p = B[0].size();
    
    vvi C(n, vi(p, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    return C;
}

vvi multiply_mod(const vvi& A, const vvi& B, int mod) {
    int n = A.size();
    int m = B.size();
    int p = B[0].size();
    
    vvi C(n, vi(p, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                C[i][j] = (C[i][j] + (A[i][k] * B[k][j]) % mod) % mod;
            }
        }
    }
    
    return C;
}

vvi matpow(vvi A, int exp, int mod) {
    int n = A.size();
    
    // Identity matrix
    vvi result(n, vi(n, 0));
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    
    // Binary exponentiation
    while (exp > 0) {
        if (exp & 1) {
            result = multiply_mod(result, A, mod);
        }
        A = multiply_mod(A, A, mod);
        exp >>= 1;
    }
    
    return result;
}
