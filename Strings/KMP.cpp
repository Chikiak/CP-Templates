#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

/*
 * KMP PATTERN MATCHING - Find all occurrences of pattern in text
 * 
 * computePrefixFunction:
 *   Arguments: s - input string
 *   Result: Returns prefix function array (pi[i] = length of longest proper 
 *           prefix of s[0..i] that is also a suffix)
 * 
 * KMP:
 *   Arguments:
 *     text    - Text to search in
 *     pattern - Pattern to search for
 *   Result: Returns vector of starting positions where pattern occurs in text
 * 
 * Time: O(n + m) where n = text length, m = pattern length
 */

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
    int n = text.size();
    int m = pattern.size();
    vi pi = computePrefixFunction(pattern);
    vi matches;
    
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            matches.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    
    return matches;
}
