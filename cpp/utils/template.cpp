//g++ -std=c++17 -Wall -Wextra -O2 -DLOCAL main.cpp -o main && ./main < in.txt
#include <bits/stdc++.h>
using namespace std;

void _print() {
    cerr << "]" << endl;
}
template<typename T, typename... V>
void _print(T t, V... v) {
    cerr << t;
    if (sizeof...(v)) cerr << ", ";
    _print(v...);
}

#ifdef LOCAL
#define dbg(x...) cerr << "[" << #x << "]: ["; _print(x)
#else
#define dbg(x...)
#define endl '\n'
#endif

#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define forn(i, n) for (int i = 0; i < n; ++i)
#define rforn(i, n) for (int i = n-1; i >= 0; --i)
#define forab(i, a, b) for (int i = a; i < b; ++i)
#define form(i, n, m, x) for (int i = n; i < m; i += x)
#define rform(i, n, m, x) for (int i = n; i >= m; i -= x)

typedef long long ll;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<ll> vll;
typedef pair<int, int> ii;
//Programa2
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif LOCAL

    //codes here
    return 0;
}