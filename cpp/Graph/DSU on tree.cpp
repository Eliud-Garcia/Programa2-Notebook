

// O(n log(n))
int n, q;
const int MAXN = 2e5 + 5;
vi g[MAXN];
int a[MAXN];//val of each node
int tam[MAXN];//subtree size
int ans[MAXN];//ans to queries
vector<array<int, 2>> queries[MAXN];
vector<map<int, int>> st(MAXN);

void dfs_sz(int u, int p){
    tam[u] = 1;
    for(int v: g[u]){
        if(v == p) continue;
        dfs_sz(v, u);
        tam[u] += tam[v];
    }
}

void dfs(int u, int p){
    int big = -1, mx = -1;
    for(int v: g[u]){
        if(v == p) continue;
        if(tam[v] > mx){
            mx = tam[v];
            big = v;
        }
    }

    for(int v: g[u]){
        if(v == p || v == big) continue;
        dfs(v, u);
    }

    if(big != -1){
        dfs(big, u);
        swap(st[u], st[big]);
        //ahora u tiene el set mas grande
    }

    //small to large
    for(int v: g[u]){
        if(v == p || v == big) continue;
        //en caso de un merge mas complejo
        //hacer una funcion merge(u, v)
        for(auto [c, occ] : st[v]){
            st[u][c] += occ;
        }
    }

    st[u][a[u]]++;//incluir u
    //ans queries
    for(auto [c, idx]: queries[u]){
        ans[idx] = st[u].count(c) ? st[u][c] : 0;
    }
}

int main() {
    cin >> n >> q;
    forab(i, 1, n + 1) cin >> a[i];
    //read tree

    //en el subarbol de u
    //¿cuantos nodos tienen color c?
    forn(i, q){
        int u, c;
        cin >> u >> c;
        queries[u].pb({c, i});
    }

    dfs_sz(1, 0);
    dfs(1, 0);

    forn(i, q){
        cout << ans[i] << ln;
    }
    return 0;
}
