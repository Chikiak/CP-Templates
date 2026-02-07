#include <bits/stdc++.h>

using namespace std;

/*
 * PASCAL'S TRIANGLE - Binomial coefficients
 * 
 * precumputePascalsTriangle:
 *   Arguments: None (uses global C array)
 *   Result: Fills C[n][k] with binomial coefficients C(n,k) for n,k ≤ 34
 *   Time: O(n²)
 */

long long C[35][35];

void precumputePascalsTriangle() {
    for (int i = 0; i <= 31; i++) {
        for (int j = 0; j <= 31; j++) {
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < 35; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }
}