#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long
#define F first
#define S second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define forn(i,s,n) for(int i = (int)s; i < (int) n; i++)
#define forv(i,s,v) for(int i = (int)s; i < (int) v.size(); i++)
#define rfor(i,n,e) for(int i = (int)n; i >=(int) e; i--)
#define pb push_back
#define pf push_front
#define lb lower_bound
#define up upper_bound
#define sz(x) (int)(x.size())
#define mid ((L + R) / 2)

typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<vi> vvi;
typedef vector<vpii> vvpii;
typedef pair<vi, vi> pvv;
//typedef unordered_map<int,int,custom_hash> umii;
typedef map<int, int> mii;
typedef map<pii,int> mpiii;
typedef map<int, pii> mipii;
typedef __int128_t int128;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int ui;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//Multiset: use less_equal & s.erase(s.find_by_order(s.order_of_key(val))) to erase duplicates

template<typename T> ostream& operator<<(ostream& os, const vector<T>& v) {
    for(int i=0; i<v.size(); ++i) os << v[i] << (i==v.size()-1 ? "" : " ");
    return os;
}

const int MOD = 1e9 + 7;
const int INF = 1e18;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return (a / gcd(a, b)) * b; }
int ceil_div(int a, int b) { return (a + b - 1) / b; }

void solve() {
    vi a = {11,2,3,4,2,13};
    cout<<a;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    //cin >> t;
    while (t--) {
        solve();
        cout <<'\n';
    }

    return 0;
}
