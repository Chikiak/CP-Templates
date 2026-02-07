// Linear Diophantine Equation solver for competitive programming
// Solves equations of form ax + by = c and counts solutions in given ranges
// find_any_solution: finds one solution (x0, y0) if exists, O(log min(a, b))
// count_solutions: counts integer solutions in specified ranges, O(1) after finding base solution
// Returns false/0 if no solution exists (when gcd(a, b) does not divide c)

#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef vector<int> vi;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    if (a == 0 && b == 0) {
        if (c == 0) {
            x0 = 0;
            y0 = 0;
            g = 0;
            return true;
        }
        return false;
    }
    if (a == 0) {
        if (c % b == 0) {
            x0 = 0;
            y0 = c / b;
            g = abs(b);
            return true;
        }
        return false;
    }
    if (b == 0) {
        if (c % a == 0) {
            x0 = c / a;
            y0 = 0;
            g = abs(a);
            return true;
        }
        return false;
    }
    g = gcd(abs(a), abs(b));
    if (c % g != 0) return false;
    int x, y;
    function<int(int, int, int&, int&)> extended_gcd = [&](int a, int b, int &x, int &y) -> int {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        int x1, y1;
        int d = extended_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - (a / b) * y1;
        return d;
    };
    extended_gcd(abs(a), abs(b), x, y);
    x *= c / g;
    y *= c / g;
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    x0 = x;
    y0 = y;
    return true;
}

int count_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy) {
    int x0, y0, g;
    if (!find_any_solution(a, b, c, x0, y0, g)) return 0;
    a /= g;
    b /= g;
    int sign_a = a > 0 ? 1 : -1;
    int sign_b = b > 0 ? 1 : -1;
    int lx1 = (minx - x0) * sign_a;
    int rx1 = (maxx - x0) * sign_a;
    int lx2 = (-(maxy - y0)) * sign_b;
    int rx2 = (-(miny - y0)) * sign_b;
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);
    if (lx > rx) return 0;
    int k_min = lx / abs(b);
    if (lx % abs(b) != 0 && lx > 0) k_min++;
    int k_max = rx / abs(b);
    if (rx % abs(b) != 0 && rx < 0) k_max--;
    return k_max - k_min + 1;
}
