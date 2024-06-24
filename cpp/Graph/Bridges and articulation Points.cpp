typedef pair<int, int> ii;

// Tarjan's Algorithm
// Finding bridges in a graph in O(N + M)
// Undirected graph.

const int MAXN = (int) 1e5 + 5; // cant nodos
vi g[MAXN];
vi tin, low;
int timer = 0;
vector<ii> bridges;
vb is_articulation, vis;
int n, m;

void dfs(int v, int p = -1){
  vis[v] = true;
  tin[v] = low[v] = timer++;
  int children = 0;
  for (int u : g[v]) {
    if (u == p) continue;
    if (vis[u]) {
      low[v] = min(low[v], tin[u]);
    } else {
      dfs(u, v);
      low[v] = min(low[v], low[u]);
      if (low[u] >= tin[v] && p != -1)
        is_articulation[v] = true;
      ++children;
      if (low[u] > tin[v])
        bridges.pb({min(u, v), max(u, v)});
    }
  }
  if (p == -1 && children > 1)
    is_articulation[v] = true;
}

int main(){
  cin >> n >> m;
  tin = vi(n + 1, -1);
  low = vi(n + 1, -1);
  vis = vb(n + 1, 0);
  is_articulation = vb(n + 1, 0);

  int a, b;
  forn(i, m) {
    cin >> a >> b;
    g[a].pb(b); g[b].pb(a);
  }
  // find bridges and articulation points
  forab (i, 1, n + 1) {
    if (!vis[i]) dfs(i);
  }
  // print articulation points
  forab (i, 1, n + 1) {
    if (is_articulation[i]) {
      cout << i << ln;
    }
  }
  // print bridges
  for (auto [u, v] : bridges) {
    cout << u << " " << v;
  }
  return 0;
}