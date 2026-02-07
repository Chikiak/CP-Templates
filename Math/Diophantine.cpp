// Linear Diophantine Equations for Competitive Programming
//
// A linear Diophantine equation has the form: ax + by = c
// where a, b, c are given integers and we need to find integer solutions (x, y)
//
// Key facts:
// - The equation has solutions if and only if gcd(a, b) divides c
// - If (x0, y0) is one solution, then all solutions are given by:
//   x = x0 + k * (b / gcd(a, b))
//   y = y0 - k * (a / gcd(a, b))
//   for any integer k
//
// This file contains:
// - solve_diophantine(a, b, c, x, y): Finds one solution to ax + by = c
// - count_solutions_in_range: Counts solutions (x, y) within given ranges
//
// Usage:
// - solve_diophantine(a, b, c, x, y): Returns true if solution exists, stores one solution in x, y
// - count_solutions_in_range: Returns count of valid solutions in specified ranges
//
// Time Complexity:
// - solve_diophantine: O(log min(a, b))
// - count_solutions_in_range: O(log min(a, b))
//
// Space Complexity: O(1)

#include <bits/stdc++.h>

using namespace std;

#define int long long

// Extended Euclidean Algorithm
// Finds integers x, y such that a*x + b*y = gcd(a, b)
// Returns: gcd(a, b)
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

// Solve linear Diophantine equation: ax + by = c
// a, b, c: coefficients of the equation
// x, y: output variables to store one solution (passed by reference)
// Returns: true if solution exists, false otherwise
// If solution exists, stores one particular solution in x and y
// Time: O(log min(a, b))
bool solve_diophantine(int a, int b, int c, int& x, int& y) {
    int g = extended_gcd(abs(a), abs(b), x, y);
    
    if (c % g != 0) {
        return false;  // No solution exists
    }
    
    // Scale the solution
    x *= c / g;
    y *= c / g;
    
    // Adjust signs if a or b were negative
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    
    return true;
}

// Count the number of solutions (x, y) to ax + by = c
// that satisfy: min_x ≤ x ≤ max_x and min_y ≤ y ≤ max_y
//
// a, b, c: coefficients of the Diophantine equation
// min_x, max_x: range for x
// min_y, max_y: range for y
// Returns: number of integer solutions in the given ranges, or -1 if infinite solutions
// Time: O(log min(a, b))
int count_solutions_in_range(int a, int b, int c, 
                              int min_x, int max_x, 
                              int min_y, int max_y) {
    int x0, y0;
    if (!solve_diophantine(a, b, c, x0, y0)) {
        return 0;  // No solutions exist
    }
    
    int g = __gcd(abs(a), abs(b));
    int dx = b / g;  // x changes by dx for each step
    int dy = a / g;  // y changes by -dy for each step
    
    // Handle special cases
    if (a == 0 && b == 0) {
        if (c == 0) return -1;  // Infinite solutions
        return 0;  // No solutions
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
    
    // General solution: x = x0 + k*dx, y = y0 - k*dy
    // We need: min_x ≤ x0 + k*dx ≤ max_x
    //          min_y ≤ y0 - k*dy ≤ max_y
    
    int k_min = LLONG_MIN / 2;
    int k_max = LLONG_MAX / 2;
    
    // Constraints from x range
    if (dx > 0) {
        k_min = max(k_min, (min_x - x0 + dx - 1) / dx);
        k_max = min(k_max, (max_x - x0) / dx);
    } else if (dx < 0) {
        k_min = max(k_min, (max_x - x0) / dx);
        k_max = min(k_max, (min_x - x0 + dx + 1) / dx);
    } else {
        // dx == 0, x is constant
        if (x0 < min_x || x0 > max_x) return 0;
    }
    
    // Constraints from y range
    if (dy > 0) {
        k_min = max(k_min, (y0 - max_y + dy - 1) / dy);
        k_max = min(k_max, (y0 - min_y) / dy);
    } else if (dy < 0) {
        k_min = max(k_min, (y0 - min_y) / (-dy));
        k_max = min(k_max, (y0 - max_y + dy + 1) / (-dy));
    } else {
        // dy == 0, y is constant
        if (y0 < min_y || y0 > max_y) return 0;
    }
    
    if (k_min > k_max) return 0;
    
    return k_max - k_min + 1;
}

// Find all solutions to ax + by = c in given ranges
// Returns: vector of pairs (x, y) representing all solutions
// Note: Use this only when the number of solutions is small
// Time: O(number of solutions + log min(a, b))
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

// Example usage:
// int main() {
//     // Solve 3x + 5y = 12
//     int x, y;
//     if (solve_diophantine(3, 5, 12, x, y)) {
//         cout << "One solution: x = " << x << ", y = " << y << endl;
//         // Outputs: x = 4, y = 0 (or x = -1, y = 3, etc.)
//     }
//     
//     // Count solutions in range
//     int count = count_solutions_in_range(3, 5, 12, 0, 10, 0, 10);
//     cout << "Number of solutions with 0 ≤ x, y ≤ 10: " << count << endl;
//     
//     // Find all solutions
//     auto all_sols = find_all_solutions(3, 5, 12, 0, 10, 0, 10);
//     cout << "All solutions:" << endl;
//     for (auto [x, y] : all_sols) {
//         cout << "x = " << x << ", y = " << y << endl;
//     }
// }
