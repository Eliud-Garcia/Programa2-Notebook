

/*
Given a undirected graph
you can remove exactly
one edge from the graph.
Your task is to minimize
the number of pairs 
of vertices (u, v)
between which there 
exists a path in this graph
*/

int n, m;
const int MAXN = 1e5 + 5;

int timer, cnt_bbc; //bicomponentes
vector<array<int, 2>> g[MAXN];
vector<int> tree[MAXN];  // bridge-tree

vector<bool> vis, is_bridge;
int tin[MAXN], low[MAXN], id[MAXN];
// u pertenece a la comp id[u]
vector<array<int, 3>> edges;

// optional
vector<int> cnt_nodes;  // nodos de la componente i
vector<int> tam; // subtree size

// Tarjan
void dfs1(int u, int p_edge) {
    tin[u] = low[u] = ++timer;
    vis[u] = true;
    for (auto& [to, idx] : g[u]) {
        //multi-aristas ok
        if (idx == p_edge) continue;
        if (vis[to]) {
            low[u] = min(low[u], tin[to]);
        } else {
            dfs1(to, idx);
            low[u] = min(low[u], low[to]);
            if (low[to] > tin[u]) {
                is_bridge[idx] = true;
            }
        }
    }
}

// assing id
void dfs2(int u) {
    vis[u] = 1;
    id[u] = cnt_bbc;
    for (auto& [to, idx] : g[u]) {
        // skip bridges
        if (is_bridge[idx]) continue;
        if (!vis[to]) dfs2(to);
    }
}

// build edge tree
void build() {
    timer = 0;
    cnt_bbc = 0;
    dfs1(1, 0);
    fill(all(vis), 0);
    forab(i, 1, n + 1) {
        if (!vis[i]) {
            cnt_bbc++;
            dfs2(i);
        }
    }
    int bridges = 0;
    forab(i, 1, m + 1) {
        if (is_bridge[i]) {
            auto [u, v, idx] = edges[i];
            tree[id[u]].pb(id[v]);
            tree[id[v]].pb(id[u]);
        }
    }
}

// do something in bridge tree
void dfs3(int u, int p) {
    tam[u] = cnt_nodes[u];
    for (int v : tree[u]) {
        if (v == p) continue;
        dfs3(v, u);
        tam[u] += tam[v];
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        vis = vb(n + 1, 0);
        is_bridge = vb(m + 1, 0);
        cnt_nodes = vi(n + 1, 0);
        tam = vi(n + 1, 0);
        edges = vector<array<int, 3>>(m + 1);

        forab(i, 1, m + 1) {
            int a, b;
            cin >> a >> b;
            g[a].pb({b, i});
            g[b].pb({a, i});
            edges[i] = {a, b, i};
        }
        
        build();
        
        forab(u, 1, n + 1) {
            cnt_nodes[id[u]]++;
        }
        
        dfs3(1, 0);  // subtree size
        
        ll mx_remove = 0;
        forab(v, 1, cnt_bbc + 1) {
            mx_remove = max(mx_remove, (ll)(n - tam[v]) * tam[v]);
        }
        
        ll cant = 1LL * n * (n - 1LL) / 2;
        cout << (cant - mx_remove) << ln;
        
        forab(i, 1, n + 1) {
            g[i].clear();
            tree[i].clear();
            tin[i] = low[i] = id[i] = 0;
        }
    }
    return 0;
}

/*
minimun number of edges
to add such that there are no
bridges in the new graph
ans = ceil(leaf / 2).

if the graph is disconnected
the answer is (hojas + 2 * solos + 1) / 2
where 
hojas = nodes where sz(tree[i]) == 1
solos = nodes where sz(tree[i]) == 0

--------------------------
if we can remove only once
edge, we can reduce the number
of bridges to
(bridges - tree diameter)
*/