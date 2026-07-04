
//O(n log n) en tiempo y memoria
const int MAXN = 1e5 + 5;
const int oo = 1e9 + 5;
int min_dis[MAXN];

vector<int> g[MAXN];
vector<array<int, 2>> ancestors[MAXN];  
// ancestros de u con su distancia
int sz[MAXN], rem[MAXN], pc[MAXN];
// subtree size, is_removed, parent in centroid tree

int dfs_sz(int u, int p = -1) {
    sz[u] = 1;
    for (int v : g[u])
        if (v != p && !rem[v])
            sz[u] += dfs_sz(v, u);
    return sz[u];
}

int centroid(int u, int p, int size) {
    for (int v : g[u])
        if (v != p && !rem[v] && sz[v] > size / 2)
            return centroid(v, u, size);
    return u;
}

void dfs_dist(int u, int p, int centroid, int d) {
    ancestors[u].push_back({centroid, d});
    for (int v : g[u])
        if (v != p && !rem[v])
            dfs_dist(v, u, centroid, d + 1);
}

void decomp(int u, int p = -1) {
    int c = centroid(u, u, dfs_sz(u));
    rem[c] = 1, pc[c] = p;
    dfs_dist(c, c, c, 0);
    for (int v : g[c])
        if (!rem[v])
            decomp(v, c);
}

int main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    fill(min_dis, min_dis + n + 1, oo);
    decomp(1);
    auto update = [&](int u) {
        for (auto& [c, d] : ancestors[u]) {
            min_dis[c] = min(min_dis[c], d);
        }
    };
    auto query = [&](int u) -> int {
        int ans = oo;
        for (auto& [c, d] : ancestors[u]) {
            ans = min(ans, min_dis[c] + d);
        }
        return ans;
    };
    update(1); //nodo inicial
    while (q--) {
        int t, v;
        cin >> t >> v;
        if (t == 1) {
            update(v);
        } else {
            cout << query(v) << ln;
        }
    }
    return 0;
}

//https://codeforces.com/contest/342/problem/E

/*
la altura del arbol es a lo mucho log(n)
Para cualquier par de nodos u, v del árbol 
original, existe un ancestro común c en el 
árbol de centroides tal que:

dist(u, v) = dist(u, c) + dist(c, v)

el nodo c puede ser de referencia
para los caminos
*/