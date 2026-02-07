#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vi computePrefixFunction(const string& s) {
    int n = s.size();
    vi pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

vi KMP(const string& text, const string& pattern) {
    string s = pattern + "#" + text;
    vi pi = computePrefixFunction(s);
    int m = pattern.size();
    vi matches;
    for (int i = m + 1; i < (int)s.size(); i++) {
        if (pi[i] == m) {
            matches.push_back(i - 2 * m);
        }
    }
    return matches;
}
