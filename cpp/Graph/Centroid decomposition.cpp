
const int MAXN = 2e5 + 5;
vi g[MAXN];
int tam[MAXN];
bool is_removed[MAXN];

int dfs_sz(int u, int p) {
    tam[u] = 1;
    for(int v: g[u]) {
        if(v == p || is_removed[v]) continue;
        dfs_sz(v, u);
        tam[u] += tam[v];
    }
    return tam[u];
}

int find_centroid(int u, int p, int tsz) {
    for(int v: g[u]) {
        if(v == p || is_removed[v]) continue;
        if(tam[v] * 2 > tsz) {
            return find_centroid(v, u, tsz);
        }
    }
    return u;
}

void yo(vi &path, int u, int p, int deep) {
    path.pb(deep);
    for(int v: g[u]) {
        if(v == p || is_removed[v]) continue;
        yo(path, v, u, deep + 1);
    }
}

ll decomp(int root, int k) {
    int c = find_centroid(root, root, dfs_sz(root, root));
    is_removed[c] = 1;

    //resolver para subarbol de centroid
    ll ans = 0;
    vi cnt(tam[root] + 1, 0);
    cnt[0] = 1;

    for(int v : g[c]) {
        if(is_removed[v]) continue;
        vi path;
        yo(path, v, v, 0);
        for (int d : path) if (k - d - 1 >= 0 && k - d - 1 < tam[root])
                ans += cnt[k - d - 1];
        for (int d : path) cnt[d + 1]++;

    }

    for (int v: g[c]) if (!is_removed[v]) ans += decomp(v, k);
    is_removed[c] = 0;
    return ans;
}

int main() {
    int n, k;
    cin >> n >> k;
    forn(i, n - 1) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    cout << 1LL * decomp(1, k) << ln;
    return 0;
}
