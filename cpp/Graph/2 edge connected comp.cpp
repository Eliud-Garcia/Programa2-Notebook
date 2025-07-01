
typedef pair<int, int> pii;

//Given a undirected graph
//you can remove exactly
//one edge from the graph.
//Your task is to minimize
//the number of pairs of vertices (u, v)
//between which there exists a path in this graph

int n, m;
const int MAXN = 1e5 + 5;

int timer, tagTree;
vector<pii> g[MAXN];
//2-edge-connected component tree
//(Bridge Tree)
vi tree[MAXN];
vb vis, isBridge;
vi tin, low;
vi id; // u pertenece a la comp id[u]
vector<array<int, 3>> edges;

//optional
vi cntNodos; //nodos de la componente i
vi tam; // subtree size

//Tarjan
void dfs1(int u, int p) {
    tin[u] = low[u] = ++timer;
    vis[u] = true;
    for(auto &[to, id]: g[u]) {
        if(to == p) continue;
        if(vis[to]) {
            low[u] = min(low[u], tin[to]);
        } else {
            dfs1(to, u);
            low[u] = min(low[u], low[to]);
            if(low[to] > tin[u]) {
                isBridge[id] = true;
            }
        }
    }
}

//assing id
void dfs2(int u) {
    vis[u] = 1;
    id[u] = tagTree;
    for(auto &[to, id]: g[u]) {
        //skip bridges
        if(isBridge[id]) continue;
        if(!vis[to]) dfs2(to);
    }
}

//build edge tree
void build() {
    timer = 0;
    tagTree = 0;
    dfs1(1, 0);
    fill(all(vis), 0);
    forab(i, 1, n + 1) {
        if(!vis[i]) {
            tagTree++;
            dfs2(i);
        }
    }
    int bridges = 0;
    forab(i, 1, m + 1) {
        if(isBridge[i]) {
            auto [u, v, idx] = edges[i];
            tree[id[u]].pb(id[v]);
            tree[id[v]].pb(id[u]);
        }
    }
}

//do something in bridge tree
// subtree size of each comp
void dfs3(int u, int p) {
    tam[u] = cntNodos[u];
    for(int v: tree[u]) {
        if(v == p) continue;
        dfs3(v, u);
        tam[u] += tam[v];
    }
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        cin >> n >> m;
        vis = vb(n + 1, 0);
        isBridge = vb(m + 1, 0);

        tin = vi(n + 1);
        low = vi(n + 1);
        id = vi(n + 1);
        cntNodos = vi(n + 1, 0);
        tam = vi(n + 1, 0);

        edges = vector<array<int, 3>>(m + 1);
        int a, b;
        forab(id, 1, m + 1) {
            cin >> a >> b;
            g[a].pb({b, id});
            g[b].pb({a, id});
            edges[id] = {a, b, id};
        }

        build();

        forab(u, 1, n + 1) {
            cntNodos[id[u]]++;
        }
        dfs3(1, 0); //subtree size
        ll mx_remove = 0;
        forab(v, 1, tagTree + 1) {
            mx_remove = max(mx_remove, (ll) (n - tam[v]) * tam[v]);
        }
        ll cant = 1LL * n * (n - 1LL) / 2;
        cout << (cant - mx_remove) << ln;
        if(t) {
            forab(i, 1, n + 1) {
                g[i].clear();
                tree[i].clear();
            }
        }
    }
    return 0;
}

//minimun number of edges
//such that there are no
//bridges in the new graph
//ans = ceil(leaf / 2)

//if we can remove only once
//edge, we can reduce the number
//of bridges to
//(bridges - tree diameter)
