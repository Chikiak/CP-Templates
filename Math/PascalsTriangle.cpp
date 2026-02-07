#include <bits/stdc++.h>

using namespace std;

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