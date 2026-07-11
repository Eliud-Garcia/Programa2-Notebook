using i128 = __int128;

struct Line {
    ll m, b; // y = m*x + b
    ll eval(ll x) const { return m * x + b; }
};

bool bad(const Line& l1, const Line& l2, const Line& l3) {
    return (i128)(l3.b - l1.b) * (l1.m - l2.m) <=
           (i128)(l2.b - l1.b) * (l1.m - l3.m);
}

struct CHT {
    vector<Line> hull;
    int ptr = 0;

    void add(ll m, ll b) {
        Line l{m, b};
        if (!hull.empty() && hull.back().m == m) {
            if (hull.back().b <= b) return; // la nueva no aporta
            hull.pop_back();
        }
        while (sz(hull) >= 2 &&
               bad(hull[sz(hull) - 2], hull.back(), l))
            hull.pop_back();
        hull.push_back(l);
        if (ptr >= sz(hull)) ptr = sz(hull) - 1;
    }

    ll query(ll x) {
        if (ptr >= sz(hull)) ptr = sz(hull) - 1;
        while (ptr + 1 < sz(hull) &&
               hull[ptr + 1].eval(x) <= hull[ptr].eval(x))
            ptr++;
        return hull[ptr].eval(x);
    }
};

int main() {
    ll n, x;
    cin >> n >> x;
    ll s[n], f[n];
    for(int i = 0; i < n; i++) cin >> s[i];
    for(int i = 0; i < n; i++) cin >> f[i];

    CHT ch;
    vector<ll> dp(n);
    ch.add(x, 0);
    for(int j = 0; j < n; j++){
        dp[j] = ch.query(s[j]);
        ch.add(f[j], dp[j]);
    }
    cout << dp[n - 1] << ln;
    return 0;
}
/*
https://cses.fi/problemset/task/2084/

dp[j] = min(dp[j], dp[i] + f[i] * s[j])

y = mx + b
mi = f[i]
b = dp[i]

x es siempre el factor que depende del 
índice que se está calculando ahora mismo 
en este caso es j
En el término cruzado, la parte que depende de j es s[j].

dp[j] = ch.query(x)
dp[j] = ch.query(s[j])

en caso de que cost(i, j) sea diferente, tratar 
de extender y organizar
*/


/*
***************************
Dynammic convex hull trick

Guarda las líneas ordenadas por 
pendiente m ascendente dentro del multiset.
CHT para maximo
*************************
*/

typedef long long int64;
typedef long double float128;

const int64 is_query = -(1LL<<62), inf = 1e18;

struct Line {
    int64 m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        int64 x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};

struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return (float128)(x->b - y->b)*(z->m - y->m) >= (float128)(y->b - z->b)*(y->m - x->m);
    }
    void insert_line(int64 m, int64 b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }

    int64 eval(int64 x) {
        auto l = *lower_bound((Line) {
            x, is_query
        });
        return l.m * x + l.b;
    }
};

int main() {
    ll n, x;
    cin >> n >> x;
    ll s[n], f[n];
    for(int i = 0; i < n; i++) cin >> s[i];
    for(int i = 0; i < n; i++) cin >> f[i];

    HullDynamic ch;
    vector<ll> dp(n);
    ch.insert_line(-x, -0); //negado para min
    for(int j = 0; j < n; j++){
        dp[j] = -ch.eval(s[j]);
        ch.insert_line(-f[j], -dp[j]);
    }
    cout << dp[n - 1] << ln;
    return 0;
}

/**
 *  Problems:
 *    http://codeforces.com/problemset/problem/319/C
 *    http://codeforces.com/contest/311/problem/B
 *    https://csacademy.com/contest/archive/task/squared-ends
 *    http://codeforces.com/contest/932/problem/F
 * */
