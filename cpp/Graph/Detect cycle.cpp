
//directed graph
const int MAXN = 1e5 + 5;
vi g[MAXN];
vi parent, color;
int n, m;
int cycle_start = -1;
int cycle_end = -1;

bool dfs(int node) {
  color[node] = 1;
  for(int next: g[node]) {
    if(color[next] == 0) {
      parent[next] = node;
      if(dfs(next)) {
        return 1;
      }
    } else if(color[next] == 1) {
      cycle_end = node;
      cycle_start = next;
      return 1;
    }
  }
  color[node] = 2;
  return 0;
}

int main() {
  cin >> n >> m;
  parent = vi(n + 1);
  color = vi(n + 1);
  int a, b;
  forn(i, m) {
    cin >> a >> b;
    g[a].pb(b);
  }
  forab(i, 1, n + 1) {
    if(color[i] == 0 && dfs(i)) break;
  }
  if(cycle_start == -1) {
    //no hay ciclo
  } else {
    //si hay ciclo
    vi path;
    path.pb(cycle_end);
    for (int i = cycle_end; i != cycle_start; i = parent[i]) {
      path.pb(parent[i]);
    }
    path.pb(cycle_end);
    cout << sz(path) << ln;
    for (int u : path) {
      cout << u <<" ";
    }
    cout << ln;
  }
  return 0;
}

//undirected graph
const int MAXN = 1e5 + 5;
vi g[MAXN];
vb vis;
vi parent;
int n, m;
int cycle_start = -1;
int cycle_end = -1;

bool dfs(int node, int par) {
  vis[node] = 1;
  parent[node] = par;
  for(int next: g[node]) {
    if(next == par) continue;
    if(vis[next]) {
      cycle_start = next;
      cycle_end = node;
      return 1;
    }
    if(!vis[next] && dfs(next, node)) return 1;
  }
  return false;
}
int main() {
  cin >> n >> m;
  vis = vb(n + 1, 0);
  parent = vi(n + 1);
  forn(i, m) {
    int a, b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
  }
  forab(i, 1, n + 1) {
    if(!vis[i] && dfs(i, -1)) break;
  }
  if(cycle_start == -1) //no hay ciclo
    else //hay ciclo
      //se puede recorrer el ciclo
      //como en la implementacion del directed graph
      return 0;
}
