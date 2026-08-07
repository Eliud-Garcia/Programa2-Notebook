
//crear la grid con los nodos
//indexados desde 1
const int MAXN = 51;
int g[MAXN][MAXN];
int res;
ll edges[MAXN];
//Complejidad =  3 ^ (n / 3)
void BronKerbosch(int n, ll R, ll P, ll X) {
    if (P == 0LL && X == 0LL) { // here we will find all possible maximal
                                // cliques (not maximum) i.e. there is no node
                                // which can be included in this set
        int t = __builtin_popcountll(R);
        res = max(res, t);
        return;
    }

    int u = 0;
    while (!((1LL << u) & (P | X))) u++;
    for (int v = 0; v < n; v++) {
        if (((1LL << v) & P) && !((1LL << v) & edges[u])) {
            BronKerbosch(n, R | (1LL << v), P & edges[v], X & edges[v]);
            P -= (1LL << v);
            X |= (1LL << v);
        }
    }
}

int max_clique(int n) {
    res = 0;
    for (int i = 1; i <= n; i++) {
        edges[i - 1] = 0;
        for (int j = 1; j <= n; j++)
            if (g[i][j])
                edges[i - 1] |= (1LL << (j - 1));
    }
    BronKerbosch(n, 0, (1LL << n) - 1, 0);
    return res;
}

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<ll> a(n + 1);
        memset(edges, 0, sizeof edges);
        memset(g, 0, sizeof g);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) continue;
                if (__gcd(a[i], a[j]) == 1) {
                    g[i][j] = 1;
                    g[j][i] = 1;
                }
            }
        }
        int ans = max_clique(n);
        cout << ans << endl;
    }
}

// maximum clique fast
//nodos indexados en 0
const int N = 155;
typedef vector<bitset<N>> graph;

struct Maxclique{
    double limit = 0.025, pk = 0;
    struct Vertex{
        int i, d = 0;
    };
    typedef vector<Vertex> vv;
    graph e;
    vv V;
    vector<vector<int>> C;
    vector<int> qmax, q, S, old;
    void init(vv &r){
        for (auto &v : r)
            v.d = 0;
        for (auto &v : r)
            for (auto j : r)
                v.d += e[v.i][j.i];
        sort(r.begin(), r.end(), [](auto a, auto b)
             { return a.d > b.d; });
        int mxD = r[0].d;
        for (int i = 0; i < sz(r); i++)
            r[i].d = min(i, mxD) + 1;
    }
    void expand(vv &R, int lev = 1){
        S[lev] += S[lev - 1] - old[lev];
        old[lev] = S[lev - 1];
        while (sz(R)){
            if (sz(q) + R.back().d <= sz(qmax))
                return;
            q.push_back(R.back().i);
            vv T;
            for (auto v : R)
                if (e[R.back().i][v.i])
                    T.push_back({v.i});
            if (sz(T)){
                if (S[lev]++ / ++pk < limit)
                    init(T);
                int j = 0, mxk = 1, mnk = max(sz(qmax) - sz(q) + 1, 1);
                C[1].clear(), C[2].clear();
                for (auto v : T){
                    int k = 1;
                    auto f = [&](int i){
                        return e[v.i][i];
                    };
                    while (any_of(C[k].begin(), C[k].end(), f))
                        k++;
                    if (k > mxk)
                        mxk = k, C[mxk + 1].clear();
                    if (k < mnk)
                        T[j++].i = v.i;
                    C[k].push_back(v.i);
                }
                if (j > 0)
                    T[j - 1].d = 0;
                for (int k = mnk; k <= mxk; k++)
                    for (int i : C[k])
                        T[j].i = i, T[j++].d = k;
                expand(T, lev + 1);
            }
            else if (sz(q) > sz(qmax))
                qmax = q;
            q.pop_back(), R.pop_back();
        }
    }
    Maxclique(graph g) : e(g), C(sz(e) + 1), S(sz(C)), old(S){
        for (int i = 0; i < sz(e); i++)
            V.push_back({i});
    }
    vector<int> solve(){ // returns the clique
        init(V), expand(V);
        return qmax;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<ll> rangos;
    map<string, int> mp;
    forn(i, n){
        int t; cin >> t;
        if(t == 1){
            rangos.pb(0);
        }else{
            string s; cin >> s;
            if(!mp.count(s)){
                mp[s] = sz(mp);
            }
            rangos.back() |= (1LL << mp[s]);
        }
    }

    graph g(sz(mp));
    for(auto [sx, u] : mp){
        forn(i, sz(rangos)){
            ll mask = rangos[i];
            if(mask & (1LL << u)){
                for(auto [sy, v] : mp){
                    if(u == v) continue;
                    if(mask & (1LL << v)){
                        g[u][v] = 1;
                    }
                }
            }
        }
    }

    //para saber el max independent set
    //se haya el clique sobre el 
    //grafo complemento
    graph gc(sz(mp));//complemento
    forn(i, sz(mp)){
        forn(j, sz(mp)){
            if(i == j) continue;
            gc[i][j] = !g[i][j];
        }
    }
    Maxclique mc(gc);
    vector<int> clique = mc.solve();
    cout << sz(clique) << ln;
    return 0;
}
