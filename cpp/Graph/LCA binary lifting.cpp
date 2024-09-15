
int n, m;
const int MAXN = 3e5 + 5;
const int LOG = 21; //calcular

vi g[MAXN];
int tin[MAXN];
int tout[MAXN];
int deep[MAXN];

int timer = 1;
int up[MAXN][LOG];
int max_up[MAXN][LOG];

map<pair<int, int>, int> weights;

void dfs(int u, int p) {
  tin[u] = timer++;
  deep[u] = deep[p] + 1;

  // initialize binary lifting arrays
  up[u][0] = p;
  max_up[u][0] = weights[ {p, u}];

  for (int v : g[u]) {
    if (v != p) {
      dfs(v, u);
    }
  }
  tout[u] = timer - 1;
}

bool is_ancestor(int x, int y) {
  return tin[x] <= tin[y] && tout[y] <= tout[x];
}

int lca(int x, int y) {
  if (is_ancestor(x, y))  return x;

  for (int i = LOG - 1; i >= 0; i--) {
    if (!is_ancestor(up[x][i], y)) {
      x = up[x][i];
    }
  }
  return up[x][0];
}

void build(int root) {
  dfs(root, root);
  forab(k, 1, LOG) {
    forab(u, 1, n + 1) {
      up[u][k] = up[up[u][k - 1]][k - 1];
      // take max of weights from left and right
      max_up[u][k] = max(max_up[u][k - 1], max_up[up[u][k - 1]][k - 1]);
    }
  }
}
//get max weight edge from (u, lcaU)
int get_max_up(int u, int v) {
  if(deep[u] < deep[v]) swap(u, v);
  int df = abs(deep[v] - deep[u]);
  int res = 0;
  forn(i, LOG) {
    if(df & (1 << i)) {
      //up the lowest node
      res = max(res, max_up[u][i]);
      u = up[u][i];
    }
  }
  return res;
}

bool cmp(array<int, 4> &a, array<int, 4> &b) {
  return a[2] < b[2];
}

int main() {
  cin >> n >> m;
  vector<array<int, 4>> edges(m);
  forn(i, m) {
    int a, b, w;
    cin >> a >> b >> w;
    edges[i] = {a, b, w, i};
    weights[ {a, b}] = w;
    weights[ {b, a}] = w;
  }

  //Kruskal
  sort(all(edges), cmp);
  UnionFind uf(n + 1);
  ll mst = 0;
  for(auto [a, b, w, id]: edges) {
    if(!uf.isSame(a, b)) {
      uf.unite(a, b);
      mst += w;
      g[a].pb(b);
      g[b].pb(a);
    }
  }

  build(1);
  vll ans(m);

  for(auto [a, b, w, id]: edges) {
    int LCA = lca(a, b);
    int mx_a = get_max_up(a, LCA);
    int mx_b = get_max_up(b, LCA);

    ll res = mst - max(mx_a, mx_b) + w;
    ans[id] = res;
  }

  forn(i, m) cout << ans[i] << ln;
  return 0;
}
