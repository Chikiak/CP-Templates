#include <bits/stdc++.h>

using namespace std;

#define int long long

int extended_gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

bool solve_diophantine(int a, int b, int c, int& x, int& y) {
    int g = extended_gcd(abs(a), abs(b), x, y);
    
    if (c % g != 0) {
        return false;
    }
    
    x *= c / g;
    y *= c / g;
    
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    
    return true;
}

int count_solutions_in_range(int a, int b, int c, 
                              int min_x, int max_x, 
                              int min_y, int max_y) {
    int x0, y0;
    if (!solve_diophantine(a, b, c, x0, y0)) {
        return 0;
    }
    
    int g = __gcd(abs(a), abs(b));
    int dx = b / g;
    int dy = a / g;
    
    if (a == 0 && b == 0) {
        if (c == 0) return -1;
        return 0;
    }
    
    if (a == 0) {
        if (c % b != 0) return 0;
        y0 = c / b;
        if (y0 < min_y || y0 > max_y) return 0;
        return max_x - min_x + 1;
    }
    
    if (b == 0) {
        if (c % a != 0) return 0;
        x0 = c / a;
        if (x0 < min_x || x0 > max_x) return 0;
        return max_y - min_y + 1;
    }
    
    int k_min = LLONG_MIN / 2;
    int k_max = LLONG_MAX / 2;
    
    if (dx > 0) {
        k_min = max(k_min, (min_x - x0 + dx - 1) / dx);
        k_max = min(k_max, (max_x - x0) / dx);
    } else if (dx < 0) {
        k_min = max(k_min, (max_x - x0) / dx);
        k_max = min(k_max, (min_x - x0 + dx + 1) / dx);
    } else {
        if (x0 < min_x || x0 > max_x) return 0;
    }
    
    if (dy > 0) {
        k_min = max(k_min, (y0 - max_y + dy - 1) / dy);
        k_max = min(k_max, (y0 - min_y) / dy);
    } else if (dy < 0) {
        k_min = max(k_min, (y0 - min_y) / (-dy));
        k_max = min(k_max, (y0 - max_y + dy + 1) / (-dy));
    } else {
        if (y0 < min_y || y0 > max_y) return 0;
    }
    
    if (k_min > k_max) return 0;
    
    return k_max - k_min + 1;
}

vector<pair<int, int>> find_all_solutions(int a, int b, int c,
                                          int min_x, int max_x,
                                          int min_y, int max_y) {
    vector<pair<int, int>> solutions;
    
    int x0, y0;
    if (!solve_diophantine(a, b, c, x0, y0)) {
        return solutions;  // No solutions
    }
    
    int g = __gcd(abs(a), abs(b));
    int dx = b / g;
    int dy = a / g;
    
    // Find the range of k
    int k_min = LLONG_MIN / 2;
    int k_max = LLONG_MAX / 2;
    
    if (dx > 0) {
        k_min = max(k_min, (min_x - x0 + dx - 1) / dx);
        k_max = min(k_max, (max_x - x0) / dx);
    } else if (dx < 0) {
        k_min = max(k_min, (max_x - x0) / dx);
        k_max = min(k_max, (min_x - x0 + dx + 1) / dx);
    }
    
    if (dy > 0) {
        k_min = max(k_min, (y0 - max_y + dy - 1) / dy);
        k_max = min(k_max, (y0 - min_y) / dy);
    } else if (dy < 0) {
        k_min = max(k_min, (y0 - min_y) / (-dy));
        k_max = min(k_max, (y0 - max_y + dy + 1) / (-dy));
    }
    
    for (int k = k_min; k <= k_max; k++) {
        int x = x0 + k * dx;
        int y = y0 - k * dy;
        if (x >= min_x && x <= max_x && y >= min_y && y <= max_y) {
            solutions.push_back({x, y});
        }
    }
    
    return solutions;
}
