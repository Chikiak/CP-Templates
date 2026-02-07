// Matrix Utilities for Competitive Programming
// 
// This file contains utilities for matrix operations, particularly useful for:
// - Solving recurrence relations (e.g., Fibonacci in O(log n))
// - Graph algorithms (counting paths of length k)
// - Linear transformations
//
// Usage:
// - vvi is defined as vector<vector<int>> where int is long long (from template.cpp)
// - multiply(A, B): Multiplies two matrices A and B
// - matpow(A, n, mod): Computes A^n mod MOD using binary exponentiation
//
// Time Complexity:
// - Matrix multiplication: O(n^3) where n is the matrix dimension
// - Matrix exponentiation: O(n^3 * log(exponent))
//
// Space Complexity: O(n^2) for storing matrices

#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef vector<int> vi;
typedef vector<vi> vvi;

// Multiply two matrices A and B
// A: n x m matrix
// B: m x p matrix
// Returns: n x p matrix (A * B)
// Note: Does NOT apply modulo during multiplication
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

// Multiply two matrices A and B with modulo
// A: n x m matrix
// B: m x p matrix
// mod: modulo value
// Returns: n x p matrix (A * B) mod 'mod'
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

// Matrix exponentiation using binary exponentiation
// A: square matrix (n x n)
// exp: exponent
// mod: modulo value
// Returns: A^exp mod 'mod'
// Note: For exp = 0, returns identity matrix
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

// Example: Computing Fibonacci number using matrix exponentiation
// F(n) = [1 1]^n * [F(1)]  =  [F(n+1)]
//        [1 0]     [F(0)]     [F(n)  ]
// 
// int fibonacci(int n, int mod) {
//     if (n == 0) return 0;
//     if (n == 1) return 1;
//     
//     vvi A = {{1, 1}, {1, 0}};
//     vvi result = matpow(A, n, mod);
//     return result[0][1];  // F(n)
// }
