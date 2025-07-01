
//use fenwick code here

//O(n*logn)
int n, m;
const int MAXN = 2e5 + 5;
const int LOG = 17;
vi g[MAXN];
int up[MAXN][LOG + 1];
int tin[MAXN], tout[MAXN];
int deep[MAXN];
int timer = 1;

void dfs(int u, int p) {
    up[u][0] = p;
    tin[u] = timer++;
    deep[u] = deep[p] + 1;
    forab(k, 1, LOG) {
        up[u][k] = up[up[u][k - 1]][k - 1];
    }
    for(int v: g[u]) {
        if(v == p) continue;
        dfs(v, u);
    }
    tout[u] = timer++;
}

int lca(int u, int v) {
    if (deep[u] < deep[v]) swap(u, v);
    int df = abs(deep[u] - deep[v]);
    for (int k = LOG - 1; k >= 0; k--) {
        if (df & (1LL << k)) {
            u = up[u][k];
        }
    }
    if (u == v) return u;
    for (int k = LOG - 1; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return up[u][0];
}

//add val to all nodes in path (a, b)
void upd_path(int a, int b, int val, BIT<int> &ft) {
    if(tin[b] < tin[a]) swap(a, b);
    int lc = lca(a, b);
    ft.upd(tin[a], + val);
    ft.upd(tin[b], + val);
    ft.upd(tout[lc], - val);
    ft.upd(tin[lc], - val);
}

//query the node value
int get_val_node(int u, BIT<int> &ft) {
    int x = ft.qry(tout[u] - 1) - ft.qry(tin[u] - 1);
    return x;
}

int main() {
    cin >> n >> m;
    forn(i, n - 1) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }
    dfs(1, 1);
    BIT<int> ft(timer + 1);
    forn(i, m) {
        int a, b;
        cin >> a >> b;
        upd_path(a, b, 1, ft);
    }

    forab(i, 1, n + 1) {
        cout << get_val_node(i, ft) << " ";
    }
    cout << ln;
    return 0;
}
